#include "window.h"
#include <QDebug>
#include <QString>
#include <QOpenGLShaderProgram>
#include <QExposeEvent>
#include <cmath>
#include "vertex.h"

const float radius = 1.0f;
        const float sqrt5 = sqrt(5.0f);
        const float phi = (1.0f + sqrt5) * 0.5f; // "golden ratio"
        // ratio of edge length to radius
        const float ratio = sqrt (10.0f + (2.0f * sqrt5)) / (4.0f * phi);
        const float a = (radius / ratio) * 0.5;
        const float b = (radius / ratio) / (2.0f * phi);

// Front Verticies
//#define VERTEX_FTR Vertex( QVector3D( 0.5f,  0.5f,  0.5f), QVector3D( 1.0f, 1.0f, 1.0f ) )
//#define VERTEX_FTL Vertex( QVector3D(-0.5f,  0.5f,  0.5f), QVector3D( 0.0f, 1.0f, 0.0f ) )
//#define VERTEX_FBL Vertex( QVector3D(-0.5f, -0.5f,  0.5f), QVector3D( 0.0f, 0.0f, 1.0f ) )
//#define VERTEX_FBR Vertex( QVector3D( 0.5f, -0.5f,  0.5f), QVector3D( 0.0f, 0.0f, 0.0f ) )

// Back Verticies
//#define VERTEX_BTR Vertex( QVector3D( 0.5f,  0.5f, -0.5f), QVector3D( 1.0f, 1.0f, 0.0f ) )
//#define VERTEX_BTL Vertex( QVector3D(-0.5f,  0.5f, -0.5f), QVector3D( 0.0f, 1.0f, 1.0f ) )
//#define VERTEX_BBL Vertex( QVector3D(-0.5f, -0.5f, -0.5f), QVector3D( 1.0f, 0.0f, 1.0f ) )
//#define VERTEX_BBR Vertex( QVector3D( 0.5f, -0.5f, -0.5f), QVector3D( 1.0f, 1.0f, 1.0f ) )

//#define VERTEX_BBL Vertex( QVector3D( 0.0f,  0.0f,  0.0f), QVector3D( 1.0f, 1.0f, 1.0f ) )
//#define VERTEX_BBR Vertex( QVector3D( 2.0f,  0.0f,  0.0f), QVector3D( 0.0f, 1.0f, 0.0f ) )
//#define VERTEX_BTR Vertex( QVector3D( 2.0f, 2.0f,  0.0f), QVector3D( 0.0f, 0.0f, 1.0f ) )
//#define VERTEX_BTL Vertex( QVector3D( 0.0f, 2.0f,  0.0f), QVector3D( 0.0f, 0.0f, 0.0f ) )

//#define VERTEX_FTR Vertex( QVector3D( 1.0f,  1.0f, 2.0f), QVector3D( 0.25f, 0.25f, 0.25f ) )
//#define VERTEX_FTL Vertex( QVector3D( 1.0f,  1.0f, 2.0f), QVector3D( 0.0f, 0.25f, 0.25f ) )
//#define VERTEX_FBL Vertex( QVector3D( 1.0f,  1.0f, 2.0f), QVector3D( 0.25f, 0.0f, 0.25f ) )
//#define VERTEX_FBR Vertex( QVector3D( 1.0f,  1.0f, 2.0f), QVector3D( 0.25f, 0.25f, 0.25f ) )

// Icosahedron
#define v1 Vertex( QVector3D(  0, b, -a ), QVector3D( 1.0f, 1.0f, 1.0f ) )
#define v2 Vertex( QVector3D(  b, a, 0 ), QVector3D( 0.0f, 1.0f, 0.0f ) )
#define v3 Vertex( QVector3D( -b, a, 0 ), QVector3D( 0.0f, 0.0f, 1.0f ) )
#define v4 Vertex( QVector3D(  0, b, a ), QVector3D( 0.0f, 0.0f, 0.0f ) )
#define v5 Vertex( QVector3D(  0, -b, a ), QVector3D( 1.0f, 1.0f, 0.0f ) )
#define v6 Vertex( QVector3D( -a, 0, b ), QVector3D( 0.0f, 1.0f, 1.0f ) )
#define v7 Vertex( QVector3D(  0, -b, -a ), QVector3D( 1.0f, 0.0f, 1.0f ) )
#define v8 Vertex( QVector3D(  a, 0, -b ), QVector3D( 1.0f, 1.0f, 1.0f ) )
#define v9 Vertex( QVector3D(  a, 0, b ), QVector3D( 0.25f, 0.25f, 0.25f ) )
#define v10 Vertex( QVector3D(-a, 0, -b ), QVector3D( 0.0f, 0.25f, 0.25f  ) )
#define v11 Vertex( QVector3D( b, -a, 0 ), QVector3D( 0.25f, 0.0f, 0.25f ) )
#define vTwelve Vertex( QVector3D(-b, -a, 0 ), QVector3D( 0.25f, 0.25f, 0.25f ) )

// Create a colored cube
static const Vertex sg_vertexes[60] = {
v1, v2, v3,
v4, v3, v2,
v4, v5, v6,
v4, v9, v5,
v1, v7, v8,
v1, v10, v7,
v5, v11, vTwelve,
v7, vTwelve, v11,
v3, v6, v10,
vTwelve, v10, v6,
v2, v8, v9,
v11, v9, v8,
v4, v6, v3,
v4, v2, v9,
v1, v3, v10,
v1, v8, v2,
v7, v10, vTwelve,
v7, v11, v8,
v5, vTwelve, v6,
v5, v9, v11
};

#undef v1
#undef v2
#undef v3
#undef v4
#undef v5
#undef v6
#undef v7
#undef v8
#undef v9
#undef v10
#undef v11
#undef vTwelve


/*******************************************************************************
 * OpenGL Events
 ******************************************************************************/

Window::Window()
{
  m_transform.translate(0.0f, 0.0f, -5.0f);
}

void Window::initializeGL()
{
  // Initialize OpenGL Backend
  initializeOpenGLFunctions();
  connect(context(), SIGNAL(aboutToBeDestroyed()), this, SLOT(teardownGL()), Qt::DirectConnection);
  connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
  printVersionInformation();

  // Set global information
  glEnable(GL_CULL_FACE);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  // Application-specific initialization
    {
      // Create Shader (Do not release until VAO is created)
      m_program = new QOpenGLShaderProgram();
      m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/simple.vert");
      m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/simple.frag");
      m_program->link();
      m_program->bind();

      // Cache Uniform Locations
      u_modelToWorld = m_program->uniformLocation("modelToWorld");
      u_worldToView = m_program->uniformLocation("worldToView");

      // Create Buffer (Do not release until VAO is created)
      m_vertex.create();
      m_vertex.bind();
      m_vertex.setUsagePattern(QOpenGLBuffer::StaticDraw);
      m_vertex.allocate(sg_vertexes, sizeof(sg_vertexes));

      // Create Vertex Array Object
      m_object.create();
      m_object.bind();
      m_program->enableAttributeArray(0);
      m_program->enableAttributeArray(1);
      m_program->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), Vertex::PositionTupleSize, Vertex::stride());
      m_program->setAttributeBuffer(1, GL_FLOAT, Vertex::colorOffset(), Vertex::ColorTupleSize, Vertex::stride());

      // Release (unbind) all
      m_object.release();
      m_vertex.release();
      m_program->release();
    }
  }


void Window::resizeGL(int width, int height)
{
  m_projection.setToIdentity();
  m_projection.perspective(45.0f, width / float(height), 0.0f, 1000.0f);
}

void Window::paintGL()
{
  // Clear
  glClear(GL_COLOR_BUFFER_BIT);

  // Render using our shader
  m_program->bind();
  m_program->setUniformValue(u_worldToView, m_projection);
  {
    m_object.bind();
    m_program->setUniformValue(u_modelToWorld, m_transform.toMatrix());
    glDrawArrays(GL_TRIANGLES, 0, sizeof(sg_vertexes) / sizeof(sg_vertexes[0]));
    m_object.release();
  }
  m_program->release();
}

void Window::teardownGL()
{
  // Actually destroy our OpenGL information
  m_object.destroy();
  m_vertex.destroy();
  delete m_program;
}

void Window::update()
{
  // Update instance information
  m_transform.rotate(0.5f, QVector3D(0.4f, 0.3f, 0.3f));

  //m_transform.grow(0.001f, 0.001f, 0.001f);
  //m_transform.translate(-0.001f, 0.0f, -0.01f);

  // Schedule a redraw
  QOpenGLWindow::update();
}

void Window::exposeEvent(QExposeEvent *ev)
{
  if (ev->region() != m_cachedRegion)
  {
    m_cachedRegion = ev->region();
    QOpenGLWindow::exposeEvent(ev);
  }
  else
  {
    ev->ignore();
  }

}

/*******************************************************************************
 * Private Helpers
 ******************************************************************************/

void Window::printVersionInformation()
{
  QString glType;
  QString glVersion;
  QString glProfile;

  // Get Version Information
  glType = (context()->isOpenGLES()) ? "OpenGL ES" : "OpenGL";
  glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

  // Get Profile Information
#define CASE(c) case QSurfaceFormat::c: glProfile = #c; break
  switch (format().profile())
  {
    CASE(NoProfile);
    CASE(CoreProfile);
    CASE(CompatibilityProfile);
  }
#undef CASE

  // qPrintable() will print our QString w/o quotes around it.
  qDebug() << qPrintable(glType) << qPrintable(glVersion) << "(" << qPrintable(glProfile) << ")";
}
