#include <strategy/local.hpp>

#include <torrent_manager.hpp>

namespace fur::strategy {

template<>
std::unique_ptr<ILocalStrategy> make_strategy_local<LocalStrategyType::Streaming>(TorrentManager& torrent) {
    return std::make_unique<StreamingStrategy>(torrent);
}

auto StreamingStrategy::extract(std::list<PieceDescriptor>& descriptors) -> Result {
    if (descriptors.empty()) return Result::ERROR(util::Error::StrategyEmpty);

    PieceDescriptor descriptor = descriptors.front();
    descriptors.pop_front();
    return Result::OK(std::move(descriptor));
}

} // namespace fur::strategy
