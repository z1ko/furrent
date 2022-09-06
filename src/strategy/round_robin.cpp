#include <strategy/global.hpp>

namespace fur::strategy {

template<>
std::unique_ptr<IGlobalStrategy> make_strategy_global<GlobalStrategyType::RoundRobin>() {
    return std::make_unique<RoundRobinStrategy>();
}

auto RoundRobinStrategy::extract(std::list<TorrentManagerRef>& torrents) -> Result {
    if (torrents.empty()) return Result::ERROR(util::Error::StrategyEmpty);

    TorrentManagerRef torrent_ref = torrents.front();
    torrents.pop_front();
    return Result::OK(std::move(torrent_ref));
}

void RoundRobinStrategy::insert(TorrentManagerRef torrent, std::list<TorrentManagerRef>& torrents) {
    torrents.push_back(torrent);
}

} // namespace fur::strategy