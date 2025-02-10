#include "Ramps.h"

void Ramps::DebugRenderer() {
	glDisable(GL_LIGHTING);

    glPushMatrix();

    glColor3f(1.0f, 0.0f, 0.0f); // Red color for the wireframe

    // Render the ramp as a wireframe
    glBegin(GL_LINE_LOOP);

    glVertex3f(startPoint.GetX(), startPoint.GetY(), startPoint.GetZ());
    glVertex3f(endPoint.GetX(), endPoint.GetY(), endPoint.GetZ());
    glVertex3f(controlPoint.GetX(), controlPoint.GetY(), controlPoint.GetZ());

    glEnd();

    // Add spheres for debugging at each point
    RenderDebugSphere(startPoint, 0.2f, 0.0f, 1.0f, 0.0f);   // Green sphere for start point
    RenderDebugSphere(endPoint, 0.2f, 1.0f, 0.0f, 0.0f);     // Red sphere for end point
    RenderDebugSphere(controlPoint, 0.2f, 0.0f, 0.0f, 1.0f); // Blue sphere for control point

    glPopMatrix();

	glEnable(GL_LIGHTING);
}

void Ramps::RenderDebugSphere(Vector3D position, float radius, float r, float g, float b) {
    glPushMatrix();

    glColor3f(r, g, b); // Set sphere color
    glTranslatef(position.GetX(), position.GetY(), position.GetZ()); // Move to position

    GLUquadric* quad = gluNewQuadric(); // Create a new quadric object
    gluSphere(quad, radius, 16, 16);    // Render the sphere
    gluDeleteQuadric(quad);             // Delete the quadric object to free memory

    glPopMatrix();
}