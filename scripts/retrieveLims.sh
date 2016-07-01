#!/bin/bash
echo "Observed"
for i in `grep "Observed" log_multiCard_T* | awk '{print $5}'`; do echo -n $i", "; done
echo "\n Expected"
for i in `grep "Expected 50" log_multiCard_T* | awk '{print $5}'`; do echo -n $i", "; done
echo "\n 1SDown"
for i in `grep "Expected 16" log_multiCard_T* | awk '{print $5}'`; do echo -n $i", "; done
echo "\n 1SUp"
for i in `grep "Expected 84" log_multiCard_T* | awk '{print $5}'`; do echo -n $i", "; done
echo "\n 2SDown"
for i in `grep "Expected  2" log_multiCard_T* | awk '{print $5}'`; do echo -n $i", "; done
echo "\n 2SUp"
for i in `grep "Expected 97" log_multiCard_T* | awk '{print $5}'`; do echo -n $i", "; done