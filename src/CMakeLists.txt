set(SOURCE_FILES
        Mercator/Area.cpp
        Mercator/AreaShader.cpp
        Mercator/BasePoint.cpp
        Mercator/Buffer.cpp
        Mercator/Buffer_impl.h
        Mercator/DepthShader.cpp
        Mercator/Effector.cpp
        Mercator/FillShader.cpp
        Mercator/Forest.cpp
        Mercator/GrassShader.cpp
        Mercator/HeightMap.cpp
        Mercator/Intersect.cpp
        Mercator/Matrix.cpp
        Mercator/Segment.cpp
        Mercator/Shader.cpp
        Mercator/ShaderFactory.cpp
        Mercator/ShaderFactory_impl.h
        Mercator/Surface.cpp
        Mercator/Terrain.cpp
        Mercator/TerrainMod.cpp
        Mercator/TerrainMod_impl.h
        Mercator/ThresholdShader.cpp
        Mercator/TileShader.cpp
        Mercator/iround.h)

set(HEADER_FILES
        Mercator/Area.h
        Mercator/AreaShader.h
        Mercator/BasePoint.h
        Mercator/Buffer.h
        Mercator/DepthShader.h
        Mercator/Effector.h
        Mercator/FillShader.h
        Mercator/Forest.h
        Mercator/GrassShader.h
        Mercator/HeightMap.h
        Mercator/Intersect.h
        Mercator/iround.h
        Mercator/Matrix.h
        Mercator/Mercator.h
        Mercator/Plant.h
        Mercator/RandCache.h
        Mercator/Segment.h
        Mercator/Shader.h
        Mercator/ShaderFactory.h
        Mercator/ShaderFactory_impl.h
        Mercator/Surface.h
        Mercator/Terrain.h
        Mercator/TerrainMod.h
        Mercator/TerrainMod_impl.h
        Mercator/ThresholdShader.h
        Mercator/TileShader.h)

wf_add_library(mercator SOURCE_FILES HEADER_FILES)
target_link_libraries(mercator PUBLIC
        wfmath::wfmath)

