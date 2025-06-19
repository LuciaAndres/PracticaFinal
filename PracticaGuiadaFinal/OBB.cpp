#include "OBB.h"


bool OBB::Intersects(const OBB& other) const {
    // Compute rotation matrix from this OBB's frame to the other's
    Matrix3x3 R = this->orientation.Transpose() * other.orientation;
    Matrix3x3 AbsR = R; // Compute absolute values
    const float* matrixData = R.GetMatrix(); // Fetch matrix values safely

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            AbsR.m[i][j] = fabs(R.m[i][j]) + 1e-6f; // Avoid floating point errors
        }
    }

    // Compute translation vector
    Vector3D translation = other.center - this->center;
    translation = this->orientation.Transpose() * translation;
/*
    std::cout << "[DEBUG] OBB Intersection Test" << std::endl;
    std::cout << "  This OBB Center: " << center << " HalfSize: " << halfSize << std::endl;
    std::cout << "  Other OBB Center: " << other.center << " HalfSize: " << other.halfSize << std::endl;
*/

    // Test each axis
    for (int i = 0; i < 3; i++) {
        float ra = this->halfSize[i];
        float rb = other.halfSize[0] * AbsR.m[i][0] +
            other.halfSize[1] * AbsR.m[i][1] +
            other.halfSize[2] * AbsR.m[i][2];
/*
        std::cout << "[DEBUG] Testing Axis " << i << ": ra = " << ra << ", rb = " << rb
            << ", Translation: " << fabs(translation[i]) << std::endl;
            */
        if (fabs(translation[i]) > ra + rb) {
            //std::cout << "[DEBUG] Separating Axis Found: NO COLLISION" << std::endl;
            return false; // Separating axis found
        }
    }

    // Test the cross products of axes (9 additional axes)
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            float ra = this->halfSize[(i + 1) % 3] * AbsR.GetValue((i + 2) % 3, j) +
                this->halfSize[(i + 2) % 3] * AbsR.GetValue((i + 1) % 3, j);

            float rb = other.halfSize[(j + 1) % 3] * AbsR.GetValue(i, (j + 2) % 3) +
                other.halfSize[(j + 2) % 3] * AbsR.GetValue(i, (j + 1) % 3);
/*
            std::cout << "[DEBUG] Cross Axis [" << i << ", " << j << "]: ra = " << ra
                << ", rb = " << rb << ", Translation: "
                << fabs(translation[i] * R.GetValue(i, j) - translation[j] * R.GetValue(j, i))
                << std::endl;
								*/
            if (fabs(translation[i] * R.GetValue(i, j) - translation[j] * R.GetValue(j, i)) > ra + rb) {
                //std::cout << "[DEBUG] Separating Axis Found: NO COLLISION" << std::endl;
                return false; // Separating axis found
            }
        }
    }

    return true; // No separating axis -> collision detected
}

AABB OBB::ToAABB() {
    Vector3D corners[8];

    // Compute the 8 corners of the OBB
    Vector3D halfExtents = halfSize;
    Matrix3x3 rotationMatrix = orientation;

    corners[0] = center + rotationMatrix * Vector3D(-halfExtents.GetX(), -halfExtents.GetY(), -halfExtents.GetZ());
    corners[1] = center + rotationMatrix * Vector3D(halfExtents.GetX(), -halfExtents.GetY(), -halfExtents.GetZ());
    corners[2] = center + rotationMatrix * Vector3D(-halfExtents.GetX(), halfExtents.GetY(), -halfExtents.GetZ());
    corners[3] = center + rotationMatrix * Vector3D(halfExtents.GetX(), halfExtents.GetY(), -halfExtents.GetZ());
    corners[4] = center + rotationMatrix * Vector3D(-halfExtents.GetX(), -halfExtents.GetY(), halfExtents.GetZ());
    corners[5] = center + rotationMatrix * Vector3D(halfExtents.GetX(), -halfExtents.GetY(), halfExtents.GetZ());
    corners[6] = center + rotationMatrix * Vector3D(-halfExtents.GetX(), halfExtents.GetY(), halfExtents.GetZ());
    corners[7] = center + rotationMatrix * Vector3D(halfExtents.GetX(), halfExtents.GetY(), halfExtents.GetZ());

    // Determine the min and max points
    Vector3D minPoint = corners[0];
    Vector3D maxPoint = corners[0];

    for (int i = 1; i < 8; i++) {
        minPoint.SetX(std::min(minPoint.GetX(), corners[i].GetX()));
        minPoint.SetY(std::min(minPoint.GetY(), corners[i].GetY()));
        minPoint.SetZ(std::min(minPoint.GetZ(), corners[i].GetZ()));

        maxPoint.SetX(std::max(maxPoint.GetX(), corners[i].GetX()));
        maxPoint.SetY(std::max(maxPoint.GetY(), corners[i].GetY()));
        maxPoint.SetZ(std::max(maxPoint.GetZ(), corners[i].GetZ()));
    }

    return AABB(minPoint, maxPoint);
}

void OBB::DebugRenderer(Color color) const
{
    Vector3D corners[8];

    // Compute the 8 corners of the OBB
    Vector3D halfExtents = halfSize;
    Matrix3x3 rotationMatrix = orientation;

    corners[0] = (rotationMatrix * Vector3D(-halfExtents.GetX(), -halfExtents.GetY(), -halfExtents.GetZ())) + center;
    corners[1] = rotationMatrix * Vector3D(halfExtents.GetX(), -halfExtents.GetY(), -halfExtents.GetZ()) + center;
    corners[2] = rotationMatrix * Vector3D(-halfExtents.GetX(), halfExtents.GetY(), -halfExtents.GetZ()) + center;
    corners[3] = rotationMatrix * Vector3D(halfExtents.GetX(), halfExtents.GetY(), -halfExtents.GetZ()) + center;
    corners[4] = rotationMatrix * Vector3D(-halfExtents.GetX(), -halfExtents.GetY(), halfExtents.GetZ()) + center;
    corners[5] = rotationMatrix * Vector3D(halfExtents.GetX(), -halfExtents.GetY(), halfExtents.GetZ()) + center;
    corners[6] = rotationMatrix * Vector3D(-halfExtents.GetX(), halfExtents.GetY(), halfExtents.GetZ()) + center;
    corners[7] = rotationMatrix * Vector3D(halfExtents.GetX(), halfExtents.GetY(), halfExtents.GetZ()) + center;

    // Define edges by connecting corner points
    int edges[12][2] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0},  // Front face
        {4, 5}, {5, 6}, {6, 7}, {7, 4},  // Back face
        {0, 4}, {1, 5}, {2, 6}, {3, 7}   // Connecting edges
    };
	glDisable(GL_LIGHTING);      // Disable lighting
    glColor3f(1.0f, 0.0f, 0.0f);  // Set color (Red for debug)
    glLineWidth(2.0f);            // Make lines more visible
    glBegin(GL_LINES);
    // Draw lines between corners
    for (int i = 0; i < 12; i++) {
        glVertex3f(corners[edges[i][0]].GetX(), corners[edges[i][0]].GetY(), corners[edges[i][0]].GetZ());

        glVertex3f(corners[edges[i][1]].GetX(), corners[edges[i][1]].GetY(), corners[edges[i][1]].GetZ());
    }

    glEnd();
	glEnable(GL_LIGHTING);      // Enable lighting
}
