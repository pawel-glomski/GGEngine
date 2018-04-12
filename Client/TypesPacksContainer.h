#pragma once
#include <unordered_map>

template<class KeyType, class PackType>
class TypesPacksContainer
{
public:

	using PacksStdContainer_t = std::unordered_map<KeyType, PackType>;

	using AddPendingPacksContainer_t = std::vector<std::pair<KeyType, PackType>>;

public:

	template<class ...CTypes>
	bool addPack(const KeyType & packKey, const TypesPack_t<CTypes...> & packToDivide);


	// instantly removes pack with the given key
	void removePack(const KeyType & packKey);


	// removes all packs
	void clear();


	void addPendingPacks();


	const PacksStdContainer_t& getStdContainer() const;


private:

	template<class ...PackTypes, class ...CTypes>
	typename std::enable_if< !TypesPack_t<CTypes...>::template AreUsed<PackTypes...>::value, bool>::type
		addPack(const KeyType &, TypesPack_t<PackTypes...> &, const TypesPack_t<CTypes...> &) { return false; }

	// adds components of entity
	template<class ...PackTypes, class ...CTypes>
	typename std::enable_if< TypesPack_t<CTypes...>::template AreUsed<PackTypes...>::value, bool>::type
		addPack(const KeyType & packKey, TypesPack_t<PackTypes...> & testPack, const TypesPack_t<CTypes... > & packToDivide)
	{
		ASSERT(!packsContainer.count(packKey), "Pack with the given key already exists");
		packsToAdd.emplace_back(std::make_pair(packKey, typename TypesPack_t<PackTypes...>::Base_t(packToDivide.get<PackTypes>()...)));
		return true;
	}


private:

	PacksStdContainer_t packsContainer;

	AddPendingPacksContainer_t packsToAdd;
};

template<class KeyType, class PackType>
template<class ...CTypes>
inline bool TypesPacksContainer<KeyType, PackType>::addPack(const KeyType & newPackKey, const TypesPack_t<CTypes...>& packToDivide)
{
	return addPack(newPackKey, PackType::getTestInstance(), packToDivide);
}

template<class KeyType, class PackType>
inline void TypesPacksContainer<KeyType, PackType>::removePack(const KeyType & packKey)
{
	packsContainer.erase(packKey);
}

template<class KeyType, class PackType>
inline void TypesPacksContainer<KeyType, PackType>::clear()
{
	packsContainer.clear();
}

template<class KeyType, class PackType>
inline void TypesPacksContainer<KeyType, PackType>::addPendingPacks()
{
	for (auto & pack : packsToAdd)
	{
		ASSERT(!packsContainer.count(pack.first), "Pack with the given key already exists");
		packsContainer.emplace(pack);
	}
	packsToAdd.clear();
}

template<class KeyType, class PackType>
inline const typename TypesPacksContainer<KeyType, PackType>::PacksStdContainer_t & TypesPacksContainer<KeyType, PackType>::getStdContainer() const
{
	return packsContainer;
}