#!/bin/bash

BASEPATH=../..

latest=$(ls -1 ${BASEPATH}/artifacts/perf/perf_*.data | sort | tail -n 1)

cp "$latest" ${BASEPATH}/data/
