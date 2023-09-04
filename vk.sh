#!/bin/bash

mkdir vulkan-sdk
cd vulkan-sdk

lastest_version=`curl -s https://vulkan.lunarg.com/sdk/files.json | sed -e 's/"/\n/g' | grep tar | head -n 1 | sed -e 's/.*x86_64-\(.*\).tar.gz/\1/'`

url="https://sdk.lunarg.com/sdk/download/${lastest_version}/linux/vulkansdk-linux-x86_64-${lastest_version}.tar.gz"

echo "download vulkan version ${lastest_version} from ${url}"

curl   --show-error -O -L "${url}" 


tar -xf vulkansdk-linux-x86_64-${lastest_version}.tar.gz

cd ${lastest_version}

source setup-env.sh

GITHUB_ENV=~/.bashrc
echo "VULKAN_SDK=${VULKAN_SDK}" >> $GITHUB_ENV
echo "PATH=${PATH}" >> $GITHUB_ENV
echo "LD_LIBRARY_PATH=${LD_LIBRARY_PATH}" >> $GITHUB_ENV
echo "VK_ADD_LAYER_PATH=${VK_ADD_LAYER_PATH}" >> $GITHUB_ENV