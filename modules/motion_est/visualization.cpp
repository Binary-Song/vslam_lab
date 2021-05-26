#include "visualization.hpp"
#include <pangolin/pangolin.h>
namespace vsl
{
    void visualize_path(vsl::Vectors3d const &pts)
    {

        pangolin::CreateWindowAndBind("path", 1920, 1080);

        glEnable(GL_DEPTH_TEST);

        // Define Projection and initial ModelView matrix
        pangolin::OpenGlRenderState s_cam(
            pangolin::ProjectionMatrix(640, 480, 420, 420, 320, 240, 0.2, 100), // set camera parameters
            pangolin::ModelViewLookAt(-2, 2, -2, 0, 0, 0, pangolin::AxisNegY)   // observation perspective
        );

        // Create Interactive View in window
        pangolin::Handler3D handler(s_cam);
        pangolin::View &d_cam = pangolin::CreateDisplay()
                                    .SetBounds(0.0, 1.0, 0.0, 1.0, -1920.0 / 1080.0)
                                    .SetHandler(&handler);

        while (!pangolin::ShouldQuit())
        {
            // Clear screen and activate view to render into
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            d_cam.Activate(s_cam);
            pangolin::glDrawAxis(3); // Draw the coordinate system

            // draw points
            glPointSize(10.0f);
            glBegin(GL_POINTS);
            glColor3f(1.0, 1.0, 0.1);

            for (auto &&pt : pts)
            {
                glVertex3f(pt(0), pt(1), pt(2));
            }
            glEnd();

            // draw lines

            glBegin(GL_LINES);
            glVertex3f((*pts.begin())(0), (*pts.begin())(1), (*pts.begin())(2));
            for (auto &&pt : pts)
            {
                glVertex3f(pt(0), pt(1), pt(2));
                glVertex3f(pt(0), pt(1), pt(2));
            } 
            glEnd();
            pangolin::FinishFrame();
        }
    }

} // namespace vsl

/*

    pangolin::CreateWindowAndBind("Main",640,480);

    glEnable(GL_DEPTH_TEST);

    // Define Projection and initial ModelView matrix
    pangolin::OpenGlRenderState s_cam(
        pangolin::ProjectionMatrix(640,480,420,420,320,240,0.2,100),// set camera parameters
        pangolin::ModelViewLookAt(-2,2,-2, 0,0,0, pangolin::AxisNegY)// observation perspective
    );

    // Create Interactive View in window
    pangolin::Handler3D handler(s_cam);
    pangolin::View& d_cam = pangolin::CreateDisplay()
            .SetBounds(0.0, 1.0, 0.0, 1.0, -640.0f/480.0f)
            .SetHandler(&handler);

    while( !pangolin::ShouldQuit() )
    {
        // Clear screen and activate view to render into
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        d_cam.Activate(s_cam);
        pangolin::glDrawAxis(3);// Draw the coordinate system
        // Render OpenGL Cube
        pangolin::glDrawColouredCube();// Draw a square on the coordinate system

        // transform the underlying objects, times and carry out a transformation
         glPushMatrix();
    	 std::vector<GLfloat > Twc = {1,0,0,0, 0,1,0,0 , 0,0,1,0 ,5,0,0,1};// transformation matrix
         glMultMatrixf(Twc.data());

        // draw points
        glPointSize(10.0f);
        glBegin(GL_POINTS);
        glColor3f(1.0,1.0,0.1);

		glVertex3f(0,0,0);

        glEnd();

        // draw a line, a pair of points is a line
        const float w = 5;
        const float h = w*0.75;
        const float z = w*0.6;
		
        glLineWidth(2);// width
        glColor3f(1.0,1.0,0);
        glBegin(GL_LINES);

		// first line connecting two points following
        glVertex3f(0,0,0);
		glVertex3f(1,1,1);
        
		// second line connecting two points following
        glVertex3f(5,1,0.5);
        glVertex3f(w,-h,z);
		// and so on ...
        glVertex3f(5,2,5);
        glVertex3f(-w,-h,z);

        glVertex3f(0,0,0);
        glVertex3f(-w,h,z);

        glVertex3f(w,h,z);
        glVertex3f(-w,h,z);

        glVertex3f(-w,h,z);
        glVertex3f(-w,-h,z);

        glVertex3f(-w,-h,z);
        glVertex3f(w,-h,z);

        glVertex3f(w,-h,z);
        glVertex3f(w,h,z);
        glEnd();

        // Swap frames and Process Events
        pangolin::FinishFrame();
    }
    
    return 0;
*/