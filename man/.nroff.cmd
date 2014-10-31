#!/bin/sh -x
nroff -ms specification.n |
sed -e 's/‐/-/g' -e 's/^/    /' -e 's/^    $//' -e 's/$/\r/' > specification2.txt
