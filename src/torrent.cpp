#include <memory>

#include "torrent.hpp"
#include "bencode_value.hpp"

TorrentFile::TorrentFile(const bencode::BencodeValue& tree) {
  // We know the torrent starts with a dict
  auto dict = dynamic_cast<const bencode::BencodeDict&>(tree).value();

  std::unique_ptr<bencode::BencodeValue>& announce_entry = (dict.at("announce"));
  this->announce_url = dynamic_cast<bencode::BencodeString&>(*announce_entry).value();

  // TODO Finish
}
