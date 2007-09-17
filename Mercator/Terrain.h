// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2003 Alistair Riddoch, Damien McGinnes

#ifndef MERCATOR_TERRAIN_H
#define MERCATOR_TERRAIN_H

#include <Mercator/Mercator.h>
#include <Mercator/BasePoint.h>

#include <wfmath/vector.h>

#include <map>
#include <list>
#include <cmath>

namespace Mercator {

class Segment;
class Shader;
class TerrainMod;
class Area;

/// \brief Class storing centrally all data about an instance of some terrain.
///
/// All the data includes:
/// - Base Points which define the terrain.
/// - Segment data which is the actual heightfields.
/// - Shaders which control how the surface appears.
/// - Surfaces which are generated by the Shaders (delegated to Segment).
/// - TerrainMods which modify the terrain data (delegated to Segment).
class Terrain {
  public:
    /// \brief STL map to store sparse array of BasePoints.
    typedef std::map<int, BasePoint> Pointcolumn;
    /// \brief STL map to store sparse array of Segment pointers.
    typedef std::map<int, Segment *> Segmentcolumn;

    /// \brief STL map to store sparse array of BasePoint columns.
    typedef std::map<int, Pointcolumn > Pointstore;
    /// \brief STL map to store sparse array of Segment pointer columns.
    typedef std::map<int, Segmentcolumn > Segmentstore;

    /// \brief STL map to store sparse array of Shader pointers.
    typedef std::map<int, Shader *> Shaderstore;

    /// \brief STL multimap to store sparse array of area modifiers.
    typedef std::multimap<int, Area *> Areastore;

    /// \brief value provided for no flags set.
    static const unsigned int DEFAULT = 0x0000;
    /// \brief set if shaders are going to be used on this terrain.
    static const unsigned int SHADED = 0x0001;
    // More options go here as bit flags, and below should be a private
    // test function
  private:
    /// \brief Bitset of option flags controlling various aspects of terrain.
    const unsigned int m_options;
    /// \brief BasePoint resolution, or distance between adjacent points.
    const int m_res;

    /// \brief 2D spatial container with all BasePoints.
    Pointstore m_basePoints;
    /// \brief 2D spatial container with pointers to all Segments.
    Segmentstore m_segments;
    /// \brief List of shaders to be applied to terrain.
    Shaderstore m_shaders;
  
    /// \brief List of areas modifiers to be applied to the terrain.
    Areastore m_areas;
  
    void addSurfaces(Segment &);
    void shadeSurfaces(Segment &);

    /// \brief Determine whether this terrain object has shading enabled.
    ///
    /// @return true if shading is enabled, false otherwise.
    bool isShaded() const {
        return ((m_options & SHADED) == SHADED);
    }
  public:
    /// \brief Height value used when no data is available.
    static const float defaultLevel;

    explicit Terrain(unsigned int options = DEFAULT,
                     unsigned int resolution = defaultResolution);
    ~Terrain();

    float get(float x, float y) const;
    bool getHeightAndNormal(float x, float y, float&, WFMath::Vector<3>&) const;

    bool getBasePoint(int x, int y, BasePoint& z) const;
    void setBasePoint(int x, int y, const BasePoint& z);

    /// \brief Set the height of the basepoint at x,y to z.
    void setBasePoint(int x, int y, float z) {
        BasePoint bp(z);
        setBasePoint(x, y, bp);
    }

    /// \brief Get a pointer to the segment which contains the coord x,y
    ///
    /// @return zero if no segment is defined at that location, or a pointer
    /// to a Segment otherwise.
    Segment * getSegment(float x, float y) const {
        int ix = (int)floor(x / m_res);
        int iy = (int)floor(y / m_res);
        return getSegment(ix, iy);
    }

    Segment * getSegment(int x, int y) const;

    /// \brief Accessor for base point resolution.
    const int getResolution() const {
        return m_res;
    }

    /// \brief Accessor for 2D sparse array of Segment pointers.
    const Segmentstore & getTerrain() const {
        return m_segments;
    }

    /// \brief Accessor for 2D sparse array of BasePoint objects.
    const Pointstore & getPoints() const {
        return m_basePoints;
    }
    
    /// \brief Accessor for list of Shader pointers.
    const Shaderstore & getShaders() const {
        return m_shaders;
    }

    /// \brief Add a new Shader to the list for this terrain.
    void addShader(Shader * t, int id);
    
    void addMod(const TerrainMod &t);
    
    void addArea(Area* a);
};

} // namespace Mercator

#endif // MERCATOR_TERRAIN_H
