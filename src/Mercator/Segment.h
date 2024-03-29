// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2003 Alistair Riddoch, Damien McGinnes

#ifndef MERCATOR_SEGMENT_H
#define MERCATOR_SEGMENT_H

#include "Mercator.h"
#include "Matrix.h"
#include "BasePoint.h"
#include "HeightMap.h"

#include <wfmath/vector.h>
#include <wfmath/axisbox.h>

#include <set>
#include <map>

namespace WFMath {
class MTRand;
}

namespace Mercator {

class Terrain;
class Surface;
class TerrainMod;
class Area;
class Shader;

// This class will need to be reference counted if we want the code to
// be able to hold onto it, as currently they get deleted internally
// whenever height points are asserted.

/// \brief Class storing heightfield and other data for a single fixed size
/// square area of terrain defined by four adjacent BasePoint objects.
class Segment {
  public:
    /// STL map of pointers to Surface objects.
    typedef std::map<int, std::unique_ptr<Surface>> Surfacestore;

    struct AreaEntry {
    	long id;
    	const Area* area;
    };

    /// STL multimap of pointers to Area objects affecting this segment.
    typedef std::multimap<int, AreaEntry> Areastore;
  private:
    /// Distance between segments
    const int m_res;
    /// Size of segment, m_res + 1
    const int m_size;
    /// Global x reference of this segment
    const int m_xRef;
    /// Global z reference of this segment
    const int m_zRef;
    /// 2x2 matrix of points which control this segment
    Matrix<2, 2, BasePoint> m_controlPoints;
    /// Pointer to buffer containing height points
    HeightMap m_heightMap;
    /// Pointer to buffer containing normals for height points
    std::vector<float> m_normals;

    /// Store of surfaces which can be rendered on this terrain
    Surfacestore m_surfaces;
    
    /// Areas which intersect this segment
    Areastore m_areas;

    /**
     * A lookup table into m_areas used when areas are removed.
     */
    std::map<long, std::multimap<int, AreaEntry>::iterator> m_areaLookup;

    /// \brief Map of TerrainMod objects that are applied to this Segment.
    std::map<long, const TerrainMod*> m_terrainMods;
  public:
    explicit Segment(int x, int z, int resolution);
    ~Segment();

    /// \brief Accessor for resolution of this segment.
    int getResolution() const {
        return m_res;
    }

    /// \brief Accessor for array size of this segment.
    int getSize() const {
        return m_size;
    }

    /// \brief Accessor for Global x reference of this segment
    int getXRef() const {
        return m_xRef;
    }

    /// \brief Accessor for Global y reference of this segment
    int getZRef() const {
        return m_zRef;
    }

    /// \brief Check whether this Segment contains valid point data.
    ///
    /// @return true if this Segment is valid, false otherwise.
    bool isValid() const {
        return m_heightMap.isValid();
    }

    void invalidate(bool points = true);

    /// \brief Set the BasePoint data for one of the four that define this
    /// Segment.
    ///
    /// @param x relative x coord of base point. Must be 0 or 1.
    /// @param z relative z coord of base point. Must be 0 or 1.
    /// @param bp BasePoint data to be used.
    void setCornerPoint(unsigned int x, unsigned int z, const BasePoint & bp) {
        m_controlPoints(x, z) = bp;
        invalidate();
    }
    
    /// \brief Accessor for 2D matrix of base points.
    const Matrix<2, 2, BasePoint> & getControlPoints() const {
        return m_controlPoints;
    }

    /// \brief Accessor for modifying 2D matrix of base points.
    Matrix<2, 2, BasePoint> & getControlPoints() {
        return m_controlPoints;
    }

    /// \brief Accessor for list of attached Surface objects.
    const Surfacestore & getSurfaces() const {
        return m_surfaces;
    }

    /// \brief Accessor for modifying list of attached Surface objects.
    Surfacestore & getSurfaces() {
        return m_surfaces;
    }

    /// \brief Accessor for buffer containing height points.
    const float * getPoints() const {
        return m_heightMap.getData();
    }

    /// \brief Accessor for write access to buffer containing height points.
    float * getPoints() {
        return m_heightMap.getData();
    }

    /// \brief Accessor for height map.
    const HeightMap& getHeightMap() const {
        return m_heightMap;
    }

    /// \brief Accessor for write access to height map.
    HeightMap& getHeightMap() {
        return m_heightMap;
    }

    /// \brief Accessor for buffer containing surface normals.
    const float * getNormals() const {
        return m_normals.data();
    }

    /// \brief Accessor for write access to buffer containing surface normals.
    float * getNormals() {
        return m_normals.data();
    }

    /// \brief Get the height at a relative integer position in the Segment.
    float get(int x, int z) const {
        return m_heightMap.get(x, z);
    }

    void getHeight(float x, float y, float &h) const;
    void getHeightAndNormal(float x, float z, float &h,
                    WFMath::Vector<3> &normal) const;
    bool clipToSegment(const WFMath::AxisBox<2> &bbox, int &lx, int &hx, int &lz, int &hz) const;


    void populate();
    void populateNormals();
    void populateSurfaces();
    void populateHeightMap(HeightMap& heightMap);

    /// \brief Accessor for the maximum height value in this Segment.
    float getMax() const { return m_heightMap.getMax(); }
    /// \brief Accessor for the minimum height value in this Segment.
    float getMin() const { return m_heightMap.getMin(); }

    /// \brief The 2d area covered by this segment
    WFMath::AxisBox<2> getRect() const;

    void updateMod(long id, const TerrainMod *t);

    void clearMods();
    
    /// \brief Accessor for multimap of Area objects.
    const Areastore& getAreas() const
    { return m_areas; }

    const std::map<long, const TerrainMod*>& getMods() const
    { return m_terrainMods; }
    
	void updateArea(long id, const Area* area, const Shader* shader);

  private:

    void applyMod(const TerrainMod *t);

    void invalidateSurfaces();

};

} // namespace Mercator

#endif // MERCATOR_SEGMENT_H
