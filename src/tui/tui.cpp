#include <algorithm>               // for max
#include <chrono>                  // for operators, chrono_literals
#include <ftxui/screen/color.hpp>  // for Color, GrayDark
#include <ftxui/screen/screen.hpp> // for Full, Screen
#include <iostream>                // for cout, ostream
#include <memory>                  // for allocator, shared_ptr
#include <optional>                // for optional
#include <sstream>                 // for istringstream
#include <string>                  // for string, operator<<
#include <thread>                  // for sleep_for
#include <vector>                  // for vector

#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp" // for hflow, paragraph, separator, hbox, vbox, filler, operator|, border, Element
#include "ftxui/dom/node.hpp"     // for Render
#include "ftxui/screen/box.hpp"   // for ftxui

using namespace ftxui;

// Helper to easily create Title with thick underline
ftxui::Element Title(const std::string &title) {
  const int underline_width = std::max<int>(1, static_cast<int>(title.size()));
  auto underline = [&]() -> Element {
    return hcenter(separatorHeavy() | size(WIDTH, EQUAL, underline_width));
  };
  return vbox({
      hcenter(text(title) | bold),
      underline(),
  });
}

int CountLines(const std::string &text) {
  return static_cast<int>(std::count(text.begin(), text.end(), '\n')) + 1;
}

// Render a paragraph with line numbers shown once per logical line.
Color CoverageColor(int percent) {
  if (percent >= 85) {
    return Color::RedLight;
  }
  if (percent >= 65) {
    return Color::Orange1;
  }
  if (percent >= 45) {
    return Color::Yellow;
  }
  return Color::Green3;
}

ftxui::Element
NumberedParagraph(const std::string &paragraph_text,
                  std::optional<int> highlighted_line = std::nullopt,
                  const std::vector<int> *coverage_values = nullptr) {
  const int total_lines = CountLines(paragraph_text);
  const int digits =
      std::max<int>(2, static_cast<int>(std::to_string(total_lines).size()));
  std::istringstream input(paragraph_text);
  std::string line;
  Elements rows;
  int line_index = 0;
  int line_number = 1;

  if (coverage_values) {
    rows.push_back(hbox({
      text(" Hit %") | bold | size(WIDTH, EQUAL, 8),
      filler(),
    }));
  }

  while (std::getline(input, line)) {
    const bool is_highlight =
        highlighted_line && *highlighted_line == line_index;

    std::string number = std::to_string(line_number);
    if (static_cast<int>(number.size()) < digits) {
      number.insert(0, digits - static_cast<int>(number.size()), ' ');
    }
    number.push_back(' ');

    Elements cells;

    if (coverage_values) {
      std::string coverage_text;
      if (line_index < static_cast<int>(coverage_values->size())) {
        coverage_text = std::to_string((*coverage_values)[line_index]) + "%";
      } else {
        coverage_text = "--%";
      }
      if (coverage_text.size() == 2) {
        coverage_text.insert(0, "  ");
      } else if (coverage_text.size() == 3) {
        coverage_text.insert(0, " ");
      }

      Color cov_color = Color::GrayDark;
      if (coverage_values &&
          line_index < static_cast<int>(coverage_values->size())) {
        cov_color = CoverageColor((*coverage_values)[line_index]);
      }

     Element coverage_cell =
         text(coverage_text) | size(WIDTH, EQUAL, 6) | color(cov_color);
      cells.push_back(coverage_cell);
    }

    Element line_number_cell =
        text(number) | size(WIDTH, EQUAL, digits + 1) |
        color(is_highlight ? Color::White : Color::GrayDark);
    cells.push_back(line_number_cell);

    Element code_cell = paragraph(line) | xflex_grow;
    if (is_highlight) {
      code_cell = code_cell | focus | bold;
    }
    cells.push_back(code_cell);

    Element row = hbox(std::move(cells));

    if (is_highlight) {
      row = row | bgcolor(Color::GrayDark);
    }

    rows.push_back(std::move(row));
    line_index++;
    line_number++;
  }

  return vbox(std::move(rows)) | xflex_grow;
}

std::vector<int> GenerateCoverageData(const std::string &source) {
  std::vector<int> data;
  std::istringstream input(source);
  std::string line;
  int index = 0;

  while (std::getline(input, line)) {
    int percent = (index * 13) % 99; // Dummy pattern between 45-99.
    data.push_back(percent);
    ++index;
  }

  return data;
}

using namespace std::chrono_literals;
int run_tui() {
  std::string text_block =
      R"(In probability theory and statistics, Bayes' theorem describes the probability of an event.
It refines the estimation using prior knowledge about related conditions.
For example, if cancer is related to age, the age data improves the risk estimate.
Using Bayes' theorem, a person's age is combined with the initial probability of cancer.
One application of the theorem is Bayesian inference inside statistical analysis.
In that setting, prior beliefs are updated whenever new evidence becomes available.
Different interpretations of probability lead to different readings of the theorem.
With the Bayesian interpretation, probabilities represent degrees of belief.
The theorem then dictates how those beliefs should change with new information.
Bayesian inference gives a disciplined process for rationally combining evidence.
The approach is now fundamental to the broader field of Bayesian statistics.
These ideas influence many practical systems, from medical decisions to search engines.
As data accumulates, posterior beliefs gradually stabilize.
Even with limited samples, the method gives a principled update.
It also underpins many machine learning pipelines for online learning.
Practical debuggers often combine coverage data with these probabilities.
Visual tools keep each column synchronized so analysts stay oriented.)";

  std::string source_snippet =
      R"(#include <vector>
#include <string>

struct Diagnostic {
  std::string message;
  int severity = 0;
};

int main() {
  auto make_formatter = [](const std::string& prefix) {
    return [=](const std::string& text) {
      return prefix + ": " + text;
    };
  };

  std::vector<Diagnostic> diagnostics = {
    {"Missing include guard", 2},
    {"Unreachable code", 1},
    {"Dangling reference captured in lambda", 3},
  };

  auto format = make_formatter("note");

  for (const auto& diag : diagnostics) {
    if (diag.severity > 2) {
      format("fatal - " + diag.message);
    } else {
      format("warn - " + diag.message);
    }
  }

  return 0;
})";

  const std::vector<int> coverage_data = GenerateCoverageData(source_snippet);

  auto make_vbox = [&](const std::string &title, Element body, int min_width,
                       int max_width) {
    return vbox({
               Title(title),
               body,
           }) |
           yflex_grow | xflex_grow | size(WIDTH, GREATER_THAN, min_width) |
           size(WIDTH, LESS_THAN, max_width);
  };

  int selected_line = 0;
  const int total_lines = static_cast<int>(coverage_data.size());

  auto content = Renderer([&] {
    Element source_body =
        NumberedParagraph(source_snippet, selected_line, &coverage_data) |
        yframe | vscroll_indicator | yflex_grow;

    Element ir_body = NumberedParagraph(text_block) | yflex_grow;

    Element info_body = paragraph(text_block) | yflex_grow;

    return vbox({
               hbox({
                   make_vbox("Source code", source_body, 50, 110),
                   separator(),
                   make_vbox("IR", ir_body, 40, 100),
                   separator(),
                   make_vbox("Line info.", info_body, 20, 30),
               }) | yflex_grow,
           }) |
           border | yflex;
  });

  auto renderer = CatchEvent(content, [&](Event event) {
    if (event == Event::ArrowDown && selected_line < total_lines - 1) {
      selected_line++;
      return true;
    }
    if (event == Event::ArrowUp && selected_line > 0) {
      selected_line--;
      return true;
    }
    return false;
  });

  auto screen = ScreenInteractive::Fullscreen();
  screen.Loop(renderer);

  return 0;
}
