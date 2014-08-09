#pragma once
#ifndef __Slide_H__
#define __Slide_H__

class Slide
{
public:
	Slide();
	~Slide();

	void SlideResolution();

	void PickModelAndComputeUnderCursorPositionAndRayDirection(int16 PositionX, int16 PositionY);
	void ComputeCursorRayDirection(int16 PositionX, int16 PositionY);

	bool CheckForCollision();
	bool CheckForCollisionTemporary(Wm5::Vector3d ResolutionVector);

	void MoveSelectedObject(Wm5::Vector3d MoveVector);

	Wm5::Vector3d ZoomSelectedModel(double dDistance, Wm5::Vector3d oDirection);

	void RotationalSnap();

	SceneObject & GetSelectedObject();
	uint16 GetSelectedObjectId();
	void SetSelectedObjectId(uint16 Id);

	enum SnapMode { Front, Back, BackNextLevel };
	enum StartingPosition { NonColliding, Colliding, Invisible };
	void NewSnap(SnapMode SnapMode);
	void NewSnap(SnapMode SnapMode, Wm5::Vector3d SnapOrigin, Wm5::Vector3d SnapDirection, StartingPosition StartingPosition/*, bool SkipVisibilityCheck*/);
	bool NewSnapB(SnapMode SnapMode, StartingPosition StartingPosition);
	bool NewSnapC(SnapMode SnapMode);

	bool m_ModelMovedByUser;
	bool m_ModelRotatedByUser;

	Wm5::Vector3d	m_CursorRayDirection;
	Wm5::Vector3d	m_UnderCursorPosition;
	Wm5::Vector3d	m_OriginalSelectedObjectPosition;

	std::vector<std::pair<std::pair<uint16, uint16>, std::pair<uint16, uint16>>> m_IntersectingPairs;

	uint16	m_SlidingObject;
	uint16	m_SlidingTriangle;
	uint16	m_SelectedTriangle;

private:
	Slide(const Slide &);
	Slide & operator =(const Slide &);

	/*public:enum SnapMode { Front, Back };
	enum StartingPosition { NonColliding, Colliding, Invisible };private:*/
	public:Wm5::Vector3d SnapOrtho(SnapMode SnapMode, StartingPosition StartingPosition, int8 TargetDepthLayer = 1);private:
	Wm5::Vector3d SnapOrtho(SnapMode SnapMode, Wm5::Vector3d SnapOrigin, Wm5::Vector3d SnapDirection, StartingPosition StartingPosition, bool SkipVisibilityCheck = false, int8 TargetDepthLayer = 1);
	public:Wm5::Vector3d SnapGeometry(SnapMode SnapMode);private:
	Wm5::Vector3d SnapGeometry(Wm5::Vector3d SnapDirection);
	double SnapGeometry2(Wm5::Vector3d SnapDirection);

	bool CheckForVisibility();

	bool TryResolveCollisionGeometry(const Wm5::Vector3d SnapDirection, double & OutputMoveAmount);
	bool FindFirstValidPosition(MultiRange<float> & Positions, const Wm5::Vector3d SnapDirection);
	bool FindFirstValidPositionB(MultiRange<float> & Positions, const Wm5::Vector3d SnapDirection, double & OutputPosition, bool & OutputHaveSkippedStartingPosition);
	bool EqualPositions(const Wm5::Vector3d Position0, const Wm5::Vector3d Position1);

	Wm5::Plane3d GetSlidingPlane(Wm5::Vector3d SelectedObjectOffset = Wm5::Vector3d::ZERO);

	double ResolveTriTriCollisionAlongVector(Wm5::Triangle3d Tri0, Wm5::Triangle3d Tri1, Wm5::Vector3d Direction);

	uint16		m_SelectedObjectId;

	public:Wm5::Plane3d		m_SlidingConstraint;

	static const double m_kBufferDistance;private:		// Buffer distance added in Geometry Collision Resolution to safeguard from the collision being detected again (i.e. distance how much objects "float" on top of surfaces)
};

#endif // __Slide_H__
