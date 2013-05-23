#include "box.h"
#include "quad.h"

Box::Box(Vector center, float width, float height, float depth, MaterialPointer material) 
  : Shape(material),
    mCenter(center), 
    mWidth(width), 
    mHeight(height), 
    mDepth(depth) {
}

Box::~Box() {
}

PatchCollectionPointer Box::splitIntoPatches() const {
  Vector xDirection = Vector(1.0f, 0.0f, 0.0f);
  Vector yDirection = Vector(0.0f, 1.0f, 0.0f);
  Vector zDirection = Vector(0.0f, 0.0f, 1.0f);
  
  float halfWidth = mWidth / 2.0f;
  float halfHeight = mHeight / 2.0f;
  float halfDepth = mDepth / 2.0f;
  
  Vector vertex0 = xDirection * (-halfWidth) + yDirection * (-halfHeight) + zDirection * halfDepth;
  Vector vertex1 = xDirection * halfWidth + yDirection * (-halfHeight) + zDirection * halfDepth;  
  Vector vertex2 = xDirection * halfWidth + yDirection * halfHeight + zDirection * halfDepth;  
  Vector vertex3 = xDirection * (-halfWidth) + yDirection * halfHeight + zDirection * halfDepth;  
  Quad frontSurface = Quad(vertex0 + mCenter, vertex1 + mCenter, vertex2 + mCenter, vertex3 + mCenter, getMaterial());

  vertex0 = xDirection * halfWidth + yDirection * (-halfHeight) + zDirection * halfDepth;
  vertex1 = xDirection * halfWidth + yDirection * (-halfHeight) + zDirection * (-halfDepth);  
  vertex2 = xDirection * halfWidth + yDirection * halfHeight + zDirection * (-halfDepth);  
  vertex3 = xDirection * halfWidth + yDirection * halfHeight + zDirection * halfDepth;  
  Quad rightSurface = Quad(vertex0 + mCenter, vertex1 + mCenter, vertex2 + mCenter, vertex3 + mCenter, getMaterial());

  vertex0 = xDirection * halfWidth + yDirection * (-halfHeight) + zDirection * (-halfDepth);
  vertex1 = xDirection * (-halfWidth) + yDirection * (-halfHeight) + zDirection * (-halfDepth);  
  vertex2 = xDirection * (-halfWidth) + yDirection * halfHeight + zDirection * (-halfDepth);  
  vertex3 = xDirection * halfWidth + yDirection * halfHeight + zDirection * (-halfDepth);  
  Quad backSurface = Quad(vertex0 + mCenter, vertex1 + mCenter, vertex2 + mCenter, vertex3 + mCenter, getMaterial());

  vertex0 = xDirection * (-halfWidth) + yDirection * (-halfHeight) + zDirection * (-halfDepth);
  vertex1 = xDirection * (-halfWidth) + yDirection * (-halfHeight) + zDirection * halfDepth;  
  vertex2 = xDirection * (-halfWidth) + yDirection * halfHeight + zDirection * halfDepth;  
  vertex3 = xDirection * (-halfWidth) + yDirection * halfHeight + zDirection * (-halfDepth);  
  Quad leftSurface = Quad(vertex0 + mCenter, vertex1 + mCenter, vertex2 + mCenter, vertex3 + mCenter, getMaterial());

  vertex0 = xDirection * halfWidth + yDirection * halfHeight + zDirection * halfDepth;
  vertex1 = xDirection * halfWidth + yDirection * halfHeight + zDirection * (-halfDepth);  
  vertex2 = xDirection * (-halfWidth) + yDirection * halfHeight + zDirection * (-halfDepth);  
  vertex3 = xDirection * (-halfWidth) + yDirection * halfHeight + zDirection * halfDepth;  
  Quad topSurface = Quad(vertex0 + mCenter, vertex1 + mCenter, vertex2 + mCenter, vertex3 + mCenter, getMaterial());

  vertex0 = xDirection * halfWidth + yDirection * (-halfHeight) + zDirection * halfDepth;
  vertex1 = xDirection * (-halfWidth) + yDirection * (-halfHeight) + zDirection * halfDepth;  
  vertex2 = xDirection * (-halfWidth) + yDirection * (-halfHeight) + zDirection * (-halfDepth);  
  vertex3 = xDirection * halfWidth + yDirection * (-halfHeight) + zDirection * (-halfDepth);  
  Quad bottomSurface = Quad(vertex0 + mCenter, vertex1 + mCenter, vertex2 + mCenter, vertex3 + mCenter, getMaterial());

  PatchCollectionPointer frontSurfacePatches = frontSurface.splitIntoPatches();
  PatchCollectionPointer rightSurfacePatches = rightSurface.splitIntoPatches();
  PatchCollectionPointer backSurfacePatches = backSurface.splitIntoPatches();
  PatchCollectionPointer leftSurfacePatches = leftSurface.splitIntoPatches();
  PatchCollectionPointer topSurfacePatches = topSurface.splitIntoPatches();
  PatchCollectionPointer bottomSurfacePatches = bottomSurface.splitIntoPatches();

  PatchCollectionPointer patches = PatchCollectionPointer(new PatchCollection());  
  patches->insert(patches->end(), frontSurfacePatches->begin(), frontSurfacePatches->end());
  patches->insert(patches->end(), rightSurfacePatches->begin(), rightSurfacePatches->end());
  patches->insert(patches->end(), backSurfacePatches->begin(), backSurfacePatches->end());
  patches->insert(patches->end(), leftSurfacePatches->begin(), leftSurfacePatches->end());
  patches->insert(patches->end(), topSurfacePatches->begin(), topSurfacePatches->end());
  patches->insert(patches->end(), bottomSurfacePatches->begin(), bottomSurfacePatches->end());

  return patches;
}
