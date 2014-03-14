    
#ifndef RECASTUTILLIB
#pragma comment(lib, "../../lib/AI/Recast.lib")
#pragma comment(lib, "../../lib/AI/Detour.lib")
#pragma comment(lib, "../../lib/AI/DebugUtils.lib")
#define RECASTUTILLIB
#endif

#pragma once
#ifndef _RECASTUTIL_H_
#define _RECASTUTIL_H_
#include <iostream>
#include <vector>
     
#include <stdio.h>
#include <cstddef>
#include <math.h>
#include <irrlicht.h>
#include "RecastNavigation\Recast.h"
#include "RecastNavigation\DetourNavMeshQuery.h"
#include "RecastNavigation\SampleInterfaces.h"
#include "RecastNavigation\DetourNavMeshBuilder.h"
#include "RecastNavigation\DetourNavMesh.h"
#include "RecastNavigation\InputGeom.h"
#include "RecastNavigation\ChunkyTriMesh.h"

#include "IPathfinding.h"

/// Tool types.
enum SampleToolType
{
	TOOL_NONE = 0,
	TOOL_TILE_EDIT,
	TOOL_TILE_HIGHLIGHT,
	TOOL_TEMP_OBSTACLE,
	TOOL_NAVMESH_TESTER,
	TOOL_NAVMESH_PRUNE,
	TOOL_OFFMESH_CONNECTION,
	TOOL_CONVEX_VOLUME,
	TOOL_CROWD,
	MAX_TOOLS
};

/// These are just sample areas to use consistent values across the samples.
/// The use should specify these base on his needs.
enum SamplePolyAreas
{
	SAMPLE_POLYAREA_GROUND,
	SAMPLE_POLYAREA_WATER,
	SAMPLE_POLYAREA_ROAD,
	SAMPLE_POLYAREA_DOOR,
	SAMPLE_POLYAREA_GRASS,
	SAMPLE_POLYAREA_JUMP,
};
enum SamplePolyFlags
{
	SAMPLE_POLYFLAGS_WALK = 0x01,       // Ability to walk (ground, grass, road)
	SAMPLE_POLYFLAGS_SWIM = 0x02,       // Ability to swim (water).
	SAMPLE_POLYFLAGS_DOOR = 0x04,       // Ability to move through doors.
	SAMPLE_POLYFLAGS_JUMP = 0x08,       // Ability to jump.
	SAMPLE_POLYFLAGS_DISABLED = 0x10,       // Disabled polygon
	SAMPLE_POLYFLAGS_ALL = 0xffff   // All abilities.
};



class RecastUtil: public IPathfinding
{
public:
	static RecastUtil* getInstance()
	{
		if ( recast == NULL ) recast = new RecastUtil();
		return recast;
	};

	~RecastUtil()
	{
		cleanup();
	};


private:
	RecastUtil()/* : verts(0),
				tris(0),

				m_ctx(0),

				m_keepInterResults(true),
				m_totalBuildTimeMs(0),
				m_triareas(0),
				m_solid(0),
				m_chf(0),
				m_cset(0),
				m_pmesh(0),
				m_dmesh(0)*/
	{
		verts = 0;
		tris = 0;

		m_ctx = 0;
		m_keepInterResults = true;
		m_totalBuildTimeMs = 0;
		m_triareas = 0;

		m_solid = 0;
		m_chf = 0;
		m_cset = 0;
		m_pmesh = 0;
		m_dmesh = 0;
		m_navMesh = 0;
		m_navQuery = 0;

		//BuildContext *ctx;

		m_ctx = new BuildContext();

		//this->setContext(ctx);
	};
	static RecastUtil *recast;
	float* verts;
	int* tris;

	BuildContext* m_ctx;


	bool m_keepInterResults;
	float m_totalBuildTimeMs;

	unsigned char* m_triareas;
	rcHeightfield* m_solid;
	rcCompactHeightfield* m_chf;
	rcContourSet* m_cset;
	rcPolyMesh* m_pmesh;
	rcConfig m_cfg;
	rcPolyMeshDetail* m_dmesh;
	void cleanup();

protected:
	InputGeom* m_geom;
	dtNavMeshQuery* m_navQuery;
	dtNavMesh* m_navMesh;

public:

	void setContext(BuildContext* ctx) { m_ctx = ctx; }

	//virtual ~RecastUtil();

	bool handleBuild(irr::scene::IMeshBuffer* buffer,
		float m_cellSize = 24.0f,
		float m_cellHeight =  0.2f,
		float m_agentHeight = 2.0f,
		float m_agentRadius = 0.6f,
		float m_agentMaxClimb = 10.0f,
		float m_agentMaxSlope = 45.0f,
		float m_regionMinSize = 8,
		float m_regionMergeSize = 20,
		bool m_monotonePartitioning = false,
		float m_edgeMaxLen = 12.0f,
		float m_edgeMaxError = 1.3f,
		float m_vertsPerPoly = 6.0f,
		float m_detailSampleDist = 6.0f,
		float m_detailSampleMaxError = 1.0f);

	bool getMeshBufferData
		(
		irr::scene::IMeshBuffer* buffer,
		std::vector<float>& verts, int& nverts,
		std::vector<int>& tris, int& ntris
		);

	bool setupIrrSMeshFromRecastDetailMesh(irr::scene::SMesh* smesh);
	void showHeightFieldInfo(const rcHeightfield& hf);
	bool getMeshDataFromPolyMeshDetail
		(
		rcPolyMeshDetail* dmesh,
		std::vector<float>& vertsOut, int& nvertsOut,
		std::vector<int>& trisOut, int& ntrisOut
		);

	bool setMeshBufferData
		(
		irr::scene::SMeshBuffer& buffer,
		const std::vector<float>& verts, int& nverts,
		const std::vector<int>& tris, int& ntris
		);

	std::vector<irr::core::vector3df> returnPath(irr::core::vector3df *pStart, irr::core::vector3df *pEnd);
};

#endif // _RECAST_UTIL_H_

