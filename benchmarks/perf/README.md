# `perf` based benchmark
The benchmark consists of having a simple use case, here `dummy_driver.c`, that makes dumm computations (just enough to have nearly 30 seconds of computation).

## Scripts
Before executing scripts, you will first need to generate the binary file with the `make` command. The `Makefile` has a `compile`, `run` and `free` routine. The default routine is `compile`, it also produces the LLVM IR representation of the dummy driver.

### `perf_record.sh`
`perf_record.sh` is the sampler script that output the perf record to the `artifacts/perf` directory. If not created, the path is created. The `.data` file produced by `perf` command has the format `perf_<data>_<hour>.data` so each sample is saved.

Note that the `artifact/*` directory **is not** versionned.

## `save_for_inputs.sh`
`save_for_inputs.sh` script copy the **last** sample file from `perf` command to the `/data` directory which contains the inputs which will be confronted the tool.

Note that the `/data` **is** versionned.

