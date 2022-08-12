#pragma once

#include <asio.hpp>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include "torrent.hpp"

/// Contains data structures and facilities for representing and discovering
/// BitTorrent peers
namespace fur::peer {
/// Represents a single peer as given by the tracker
class Peer {
 public:
  explicit Peer(uint32_t ip, uint16_t port);

  /// Combines the ip and port of the peer into a X.Y.Z.W:PORT string
  /// \return The combined string
  [[nodiscard]] std::string address() const;

  void connect();

 private:
  uint32_t ip;
  uint16_t port;

  std::optional<asio::ip::tcp::socket> socket;
};

/// The response sent from the tracker when announcing
struct AnnounceResult {
  /// How often (in seconds) we're expected to re-announce ourselves and refresh
  /// the list of peers
  int interval;
  /// The list of peers that we can download the file from
  std::vector<Peer> peers;
};

/// Announce ourselves to the tracker and get a list of peers to download the
/// file from
[[nodiscard]] AnnounceResult announce(const torrent::TorrentFile& torrent_f);
}  // namespace fur::peer
