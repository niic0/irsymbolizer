void Samples2ir(const std::string &ModuleName, uint64_t PC_addr, const std::string &LlvmIr) {
  Expected<DILineInfo> lineInfo = symbolizeCodeWrapper(ModuleName, PC_addr);

  const char *cmd =
    "perf script -i perf.data -F ip | sed '/^#/d'";

  FILE *fp = popen(cmd, "r");
  if (!fp) {
    WithColor::error() << "Failed to execute the perf script command\n";
  }

  char line[256];
  while (fgets(line, sizeof(line), fp)) {
    // remove trailing newline
    line[strcspn(line, "\n")] = '\0';

    if (line[0] == '\0')
      continue;

    printf("Address: %s\n", line);
  }

  pclose(fp);

  return lineInfo;
}
