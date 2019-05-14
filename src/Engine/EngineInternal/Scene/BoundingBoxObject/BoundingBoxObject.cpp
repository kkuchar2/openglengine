#include "BoundingBoxObject.h"


void BoundingBoxObject::update(const bool & refreshMatrices) {

}

void BoundingBoxObject::update(const Transform & t, const BoundingBox & bb, const bool & refreshMatrices) {


    transform.position = t.position;
    transform.pivot = t.scale * bb.center;
    transform.rotation = t.rotation;
    transform.scale = t.scale * bb.size;

    if (!refreshMatrices) return;

    transform.positionMatrix = MatrixUtils::translationMatrix(transform.position);
    transform.scaleMatrix = MatrixUtils::scaleMatrix(transform.scale);
    transform.rotationMatrix = MatrixUtils::rotationMatrix(transform.rotation);
    transform.pivotMat = MatrixUtils::translationMatrix(transform.pivot);

    transform.calculateModelMatrix2();
}