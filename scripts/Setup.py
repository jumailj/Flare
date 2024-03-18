import os
import subprocess
import CheckPython

#make sure everyting we need is installed
CheckPython.ValidatePackages();

import Vulkan

#Change from scripts directory to root
os.chdir('../')

#download and extract vulkan.
Vulkan.InstallVulkanSDK()

#running premake
print("Running premakee...")
subprocess.call(["./premake5", "gmake"])