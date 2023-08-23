#include <jni.h>
#include <iostream>
#include <vector>
#include <string>
#include <dirent.h>
#include <dlfcn.h>
#include <algorithm>

bool isexpectedfile(const std::string& filename, const std::vector<std::string>& expectedfiles) {
    return std::find(expectedfiles.begin(), expectedfiles.end(), filename) != expectedfiles.end();
}

std::vector<std::string> getfiles(const std::string& directorypath) {
    std::vector<std::string> files;
    DIR* dir;
    struct dirent* entry;

    dir = opendir(directorypath.c_str());
    if (dir == nullptr) {
        std::terminate();
    }

    while ((entry = readdir(dir)) != nullptr) {
        if (entry->d_type == DT_REG) {
            std::string filename = entry->d_name;
            files.push_back(filename);
        }
    }

    closedir(dir);

    return files;
}

void verifyfiles(const std::string& directorypath, const std::vector<std::string>& expectedfiles) {
    std::vector<std::string> files = getfiles(directorypath);
    for (const auto& file : files) {
        if (!isexpectedfile(file, expectedfiles)) {
            std::terminate();
        }
    }
}

jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
    std::string directorypath = "/data/data/com.rockstargames.gtasa/libs/";
    std::vector<std::string> expectedfiles = {
        "libfile1.so",
        "libfile2.so",
        "libfile3.so"
    };

    verifyfiles(directorypath, expectedfiles);

    return JNI_VERSION_1_4;
}
