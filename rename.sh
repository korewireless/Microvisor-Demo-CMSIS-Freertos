#!/bin/bash

for file in $1.*; do
    ext="${file##*.}"
    mv "$file" "$2.${ext}"
done
