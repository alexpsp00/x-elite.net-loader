#pragma once

#include <Windows.h>
#include <BlackBone/Config.h>
#include <BlackBone/Process/Process.h>
#include <BlackBone/PE/PEImage.h>
#include <BlackBone/Misc/Utils.h>
#include <BlackBone/Misc/DynImport.h>




using namespace blackbone;

void inject(std::vector < BYTE > &image);