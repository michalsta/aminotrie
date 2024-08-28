#include <cassert>
#include <cstring> // std::strerror
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "fasta.h"

SeqSet SeqSet::FromFASTA(const std::string &file_path) {
  std::ifstream file;
  file.exceptions(std::ifstream::badbit);
  file.open(file_path);
  file.exceptions();
  std::vector<std::vector<std::uint8_t>> seqs;
  std::vector<std::string> ids;
  std::string line;

  while (std::getline(file, line)) {
    std::cerr << line << '\n';
    if (line[0] == '>') {
      seqs.push_back({});
      ids.push_back(line.substr(1));
    } else {
      if (seqs.size() > 0) {
        std::vector<uint8_t> &ss = seqs.back();
        for (uint8_t c : line)
          ss.push_back(AminoAcidsMap[c]);
      };
    }
  }

  return SeqSet(std::move(seqs), std::move(ids));
}

int main(int argc, char** argv) {
  std::string path;
  if (argc == 1)
    path = "/mnt/storage/git/aminotrie/example.fasta";
  else
    path = argv[1];
  SeqSet S(SeqSet::FromFASTA(path));
}
