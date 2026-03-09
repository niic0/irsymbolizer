#!/bin/bash

BASEPATH=../..

mkdir -p ${BASEPATH}/artifacts/perf

perf record -o ${BASEPATH}/artifacts/perf/perf_$(date +%Y%m%d_%H%M%S).data -- ./dummy_driver 2048
