/*
 * Skin.h
 *
 *  Created on: Oct 8, 2011
 *      Author: mluffel
 */

#ifndef SKIN_H_
#define SKIN_H_

#include <vector>
#include <map>

#include <XnCppWrapper.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>

#include "Body/Skeleton/Skeleton.h"

namespace Body
{

const int MAX_BINDINGS = 2;



struct SkinBinding {
	int index[MAX_BINDINGS];
	float weight[MAX_BINDINGS];
	
	SkinBinding();
};

class Skin
{
public:
	
	/**
	 * This defines the order of bones.
	 * Call this once when creating a skin.
	 */
	void addBone(std::string joint_key);
	
	/**
	 * Call this before adding points to bones, just once.
	 */	 
	void setNumPoints(int num_points);

	/**
	 * Attach a point to a bone with a given weight.
	 * A point can have at most two attached bones.
	 */
	void addPointToBone(int point_index, int bone_index, float weight);
	
	/**
	 * Precompute the local coordinates of each point.
	 * Pass in the canonical pose, only once to compute local coordinates for each limb.
	 */
	void bind(pcl::PointCloud<pcl::PointXYZRGB>::Ptr all_points, const Body::Skeleton::Pose::Ptr bind_pose);
	
	/*
	 * Renders mesh via OpenGL. Uses vertex shaders to compute posed poins on the GPU-side.
	 */
	void renderPosed(const Body::Skeleton::Pose::Ptr pose);
	
	/**
	 * Get the points, skinned with the current pose.
	 * Runs on the CPU side.
	 */
	const pcl::PointCloud<pcl::PointXYZRGB>::Ptr pose(const Body::Skeleton::Pose::Ptr pose) const;

	Skin();

private:
	/**
	 * Association between skin points and bones, including weights.
	 * At most MAX_BINDINGS per skin point.
	 */
	std::vector<SkinBinding> bindings;
	
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr input_points;
	
	/*
	 * Input points expressed in local coordinates of the bone.
	 * This is empty until
	 */
	pcl::PointCloud<pcl::PointXYZ> bound_points[MAX_BINDINGS];
	
	/**
	 * Used during bind and pose to match joints with the correct indices.
	 */
	typedef std::map<std::string, int> NameToIndex;
	NameToIndex limb_map;
	int num_bones;
};

}

#endif /* SKIN_H_ */
