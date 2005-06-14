// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2003 Alistair Riddoch

#ifndef MERCATOR_FILL_GRASS_SHADER_H
#define MERCATOR_FILL_GRASS_SHADER_H

#include <Mercator/Shader.h>
#include <Mercator/Surface.h>

/* alpha ^
 *       |
 *     1 |_______________________ cutoff
 *       |                       \ 
 *       |                        \ 
 *       |                         \ 
 *       |                          \ 
 *       |                           \ 
 *       |                            \ 
 *       |                             \ 
 *       |                              \ 
 *       |                               \ 
 *       |                                \  intercept
 *     0 |_________________________________\_________________________> slope
 *
 * This shader is used to add grassy vegetation to some terrain.
 * The mask generated by this shader depends on two factors. The altitude
 * of the terrain, and its slope. Two parameter specify the low and high
 * altitude values between which vegetation grows. The low value will typically
 * be just above sea level, and the high value could be anything up to the
 * height above which plants cannot grow.
 *
 * The cutoff parameter specifies the slope below which the vegetation is
 * completely opaque. The intercept parameter specifies the slope above which
 * vegetetation will not grow on the terrain. Between these values the
 * vegetation is blended onto the terrain to give an impression of a light
 * covering.
 */

namespace Mercator {

class GrassShader : public Shader {
  private:
    float m_lowThreshold;
    float m_highThreshold;
    float m_cutoff;
    float m_intercept;

    ColorT slopeToAlpha(float height, float slope) const;
  public:
    static const std::string key_lowThreshold;
    static const std::string key_highThreshold;
    static const std::string key_cutoff;
    static const std::string key_intercept;

    static const float default_lowThreshold;
    static const float default_highThreshold;
    static const float default_cutoff;
    static const float default_intercept;

    explicit GrassShader(float lowThreshold = default_lowThreshold,
                         float highThreshold = default_highThreshold,
                         float cutoff = default_cutoff,
                         float intercept = default_intercept);
    explicit GrassShader(const Parameters & params);
    virtual ~GrassShader();

    const float lowThreshold() const { return m_lowThreshold; }
    const float highThreshold() const { return m_highThreshold; }
    const float cutoff() const { return m_cutoff; }
    const float intercept() const { return m_intercept; }

    virtual bool checkIntersect(const Segment &) const;
    virtual void shade(Surface &) const;
};

} // namespace Mercator

#endif // MERCATOR_FILL_GRASS_SHADER_H
