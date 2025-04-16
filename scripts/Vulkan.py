import os
import subprocess
import sys

import Utils

VULKAN_SDK_INSTALLER_URL = 'https://sdk.lunarg.com/sdk/download/1.3.275.0/linux/vulkansdk-linux-x86_64-1.3.275.0.tar.xz'
FLARE_VULKAN_VERSION = '1.3.275.0'
VULKAN_SDK_EXE_PATH = 'Flare/vendor/VulkanSDK/'
VULKAN_DOWNLOAD_PATH = 'Flare/vendor/VulkanSDK/VulKanSDK.tar.xz'

def InstallVulkanSDK():
    print('Downloading {} to {}'.format(VULKAN_SDK_INSTALLER_URL, VULKAN_DOWNLOAD_PATH))
    Utils.DownloadFile(VULKAN_SDK_INSTALLER_URL, VULKAN_DOWNLOAD_PATH)
    print("Done!")
    print("Extracting Vulkan...")
    #extract .tar.xz file
    Utils.extract_tar_xz(VULKAN_DOWNLOAD_PATH, VULKAN_SDK_EXE_PATH)