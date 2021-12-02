#include <string>
#include <iostream>
#include <filesystem>
#include <cstring>
#include <vector>
namespace fs = std::filesystem;

void get_FilePaths(std::vector<fs::path>& filePaths, std::string iniDir, std::string fileExtension);
void copy_Files(std::vector<fs::path>& filePaths, std::vector<bool>& filePathState, fs::path targetPath);
void delete_Files(std::vector<fs::path>& filePaths, std::vector<bool>& filePathState, fs::path targetPath);

int main(void) {
    std::string iniDir;
    std::string fileExtension;
    std::string targetDir;
    
    std::cout << "Enter file directory\n";
    std::cin >> iniDir;
    std::cout << "Enter file extension\n";
    std::cin >> fileExtension;
    std::cout << "Enter target directory\n";
    std::cin >> targetDir;

    std::vector<fs::path> filePaths;
    fs::path targetPath(targetDir);

    get_FilePaths(filePaths, iniDir, fileExtension);

    std::vector<bool> filePathState(filePaths.size(), 0);

    copy_Files(filePaths, filePathState, targetDir);
    delete_Files(filePaths, filePathState, targetDir);

    filePaths.clear();

    return 0;
}

void get_FilePaths(std::vector<fs::path>& filePaths, std::string iniDir, std::string fileExtension) {
    for (const auto& entry : fs::directory_iterator(iniDir)) {
        if (entry.path().extension() == fileExtension) {
            filePaths.push_back(entry.path());
        }
    }
}

void copy_Files(std::vector<fs::path>& filePaths, std::vector<bool>& filePathState, fs::path targetPath) {
    int i = 0;

    const auto copyOptions = fs::copy_options::update_existing;
    
    for (auto const& path : filePaths) {
        try {
            fs::copy_file(path, targetPath / path.filename(), copyOptions);
        }
        catch (fs::filesystem_error const& ex) {
            filePathState[i] = 1;
            std::cout
                << "what():  " << ex.what() << '\n'
                << "path1(): " << ex.path1() << '\n'
                << "path2(): " << ex.path2() << '\n'
                << "code().value():    " << ex.code().value() << '\n'
                << "code().message():  " << ex.code().message() << '\n'
                << "code().category(): " << ex.code().category().name() << '\n';
        }
        i++;
    }
}

void delete_Files(std::vector<fs::path>& filePaths, std::vector<bool>& filePathState, fs::path targetPath) {
    int i = 0;

    for (auto const& path : filePaths) {
        if (filePathState[i] == 0) {
            try {
                fs::remove(path);
            }
            catch (fs::filesystem_error const& ex) {
                std::cout
                    << "what():  " << ex.what() << '\n'
                    << "path1(): " << ex.path1() << '\n'
                    << "path2(): " << ex.path2() << '\n'
                    << "code().value():    " << ex.code().value() << '\n'
                    << "code().message():  " << ex.code().message() << '\n'
                    << "code().category(): " << ex.code().category().name() << '\n';
            }

            std::cout << path << " was successfully moved to " << targetPath << std::endl;
        }
        else {
            std::cout << path << " was not successfully moved" << std::endl;
        }
    }
}
