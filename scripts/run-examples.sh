#!/usr/bin/env bash

bin=./bin/x
ext=xasm
dir=examples

for file in $(find $dir -name "*.${ext}" -not -name "*.test.${ext}" -not -name "*.error.${ext}" -not -name "*.play.${ext}"); do
    echo "[run] $file"
    ${bin} run $file
done

for file in $(find $dir -name "*.test.${ext}"); do
    echo "[test] $file"
    ${bin} run $file > $file.out
done

for file in $(find $dir -name "*.error.${ext}"); do
    echo "[error] $file"
    ${bin} run $file 2> $file.err || true
done
