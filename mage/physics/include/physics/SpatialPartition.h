#pragma once

#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace mage
{
namespace physics
{

/////////////////////////////////////////////////
/// This is needed to use std pair in hash tables
/////////////////////////////////////////////////
struct PairHash
{
  template <typename T1, typename T2>
  std::size_t operator()(const std::pair<T1, T2>& _pair) const
  {
    return std::hash<T1>()(_pair.first) ^ std::hash<T2>()(_pair.second);
  }
};

/////////////////////////////////////////////////
/// Partitions the template parameter based on bassed bounds with the data.
/////////////////////////////////////////////////
template <typename T> class SpatialPartition
{
  using Key = std::pair<std::int32_t, std::int32_t>;
  using Value = std::vector<T>;

public:
  explicit SpatialPartition(float _cellSize)
      : m_buckets()
      , m_cellSize(_cellSize)
  {
  }

  /////////////////////////////////////////////////
  /// add an item to the hash table
  /////////////////////////////////////////////////
  void AddItem(T _item, float _x, float _z, float _sizeX, float _sizeZ)
  {
    std::unordered_set<Key, PairHash> cellIDs =
        GetResidingCellsID(_x, _z, _sizeX, _sizeZ);

    for (auto& id : cellIDs)
    {
      m_buckets[id].emplace_back(std::move(_item));
    }
  }

  /////////////////////////////////////////////////
  /// clear the buckets
  /////////////////////////////////////////////////
  void ClearBuckets()
  {
    int saveSize = m_buckets.size();
    m_buckets.clear();
    m_buckets.reserve(saveSize);
  }

  void Reserve(std::size_t _count) { m_buckets.reserve(_count); }

  std::unordered_map<Key, Value, PairHash>& GetBuckets() { return m_buckets; }

private:
  /////////////////////////////////////////////////
  /// get the hashed ids of the buckets that this position resides in
  /////////////////////////////////////////////////
  std::unordered_set<Key, PairHash>
  GetResidingCellsID(float _x, float _z, float _sizeX, float _sizeZ)
  {
    // create the set of bucket IDs that this item resides in
    // sets have a faster find function than vectors, so it's appropriate here
    std::unordered_set<Key, PairHash> bucketsItemIsIn;

    // get the min coordinate of the box
    float minXAxis = _x - _sizeX;
    float minZAxis = _z - _sizeZ;

    float maxXAxis = _x + _sizeX;
    float maxZAxis = _z + _sizeZ;

    AddBucket(minXAxis, minZAxis, bucketsItemIsIn);
    AddBucket(minXAxis, maxZAxis, bucketsItemIsIn);
    AddBucket(maxXAxis, minZAxis, bucketsItemIsIn);
    AddBucket(maxXAxis, maxZAxis, bucketsItemIsIn);

    return bucketsItemIsIn;
  }

  /////////////////////////////////////////////////
  /// Adds a bucket ID to the vector of bucket IDs based on the world
  /////////////////////////////////////////////////
  void AddBucket(float _x, float _z,
                 std::unordered_set<Key, PairHash>& _bucketToAdd)
  {
    // hash the world coordinate point
    Key cellID = Hash(_x, _z);

    // check if the bucket with this ID already exists in the set of bucket IDs
    if (_bucketToAdd.find(cellID) == _bucketToAdd.end())
    {
      // Add it if it doesn't exist already
      _bucketToAdd.insert(cellID);
    }
  }

  /////////////////////////////////////////////////
  /// Hashes a world point to the ID of the bucket that the point resides
  /////////////////////////////////////////////////
  Key Hash(float _x, float _z)
  {
    // the bucked ID
    Key cellID((int)(_x / m_cellSize), (int)(_z / m_cellSize));

    if (_x < 0.0f)
    {
      --cellID.first;
    }
    if (_z < 0.0f)
    {
      --cellID.second;
    }

    // return the bucket ID
    return cellID;
  }

private:
  std::unordered_map<Key, Value, PairHash> m_buckets;

  float m_cellSize; ///< size of the cells in every axis
};

} // namespace physics
} // namespace mage