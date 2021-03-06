/*
 * Skeleton.h
 *
 *  Created on: Oct 8, 2011
 *      Author: webaba
 */

#ifndef BODYSEGMENTATION_H_
#define BODYSEGMENTATION_H_

#include <vector>
#include <map>
#include <string>
#include <Body/Skin.h>
#include <Body/Skeleton/Skeleton.h>
#include <Body/BodyPointCloud.h>
#include <iostream>
#include <pcl/point_types.h>
#include "pcl/io/pcd_io.h"
#include <math.h>
#include <sstream>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>

namespace Body {





class BodySegmentation {
public:

	/**
	 * Constructor to build the segmentator from a just a Yaml skeleton file.
	 * Really this would be a "Weightor" not a segmentator
	 * (call weight() on each point you want weights for).
	 */
	BodySegmentation(std::string const skeletonfilename);

	/**
	 * Constructor to build the segmentator from a Yaml skeleton file.
	 */
	BodySegmentation(std::string const skeletonfilename, pcl::PointCloud<
			pcl::PointXYZRGB>::Ptr bodycloud_, Skin *pskin_);

	/**
	 * Constructor to build the segmentator from a skeleton pose.
	 */
	BodySegmentation(Skeleton::Pose *pose_,
			pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr bodycloud_, Skin *pskin_);

	/**
	 * Visualization.
	 */
	//void visualize(int index);

	/**
	 * Computes the correspondances and fills the Skin attribute.
	 */
	void run();


	// TODO don't store these, store a Skeleton::Pose instead
	std::vector<pcl::PointXYZ> joints;
	std::vector<pcl::PointXYZ> bones;


private:

	/**
	 * Pointer to the skinning object that will be modified.
	 */
	Skin *pskin;

	/**
	 * Pointer to the skeleton pose.
	 */
	Skeleton::Pose *sk_pose;

	/**
	 * Pointer to the body point cloud.
	 */
	pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr bodycloud;

	// Initializations methods
	void initJoints();
	void initJointsFromYaml(string skeleton_yaml_filename);

	void initBones();

	// Skin attributes


	// Mapping attributes and methods for keys

	//std::map<std::string, int> indexFromKey;
	//void initIndexMap();
	//int getIndexFromKey(std::string const key);
	//std::string getKeyFromBoneIndex(int bone);

	// Segmentation attributes

	std::vector<pcl::PointCloud<pcl::PointXYZRGB>::Ptr> limbs_clouds;

	// Skeleton
	Skeleton::Pose::JointPoses joint_poses;

};

}

#endif /* BODYSEGMENTATION_H_ */
