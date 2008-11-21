/**********************************************************************
  Cube - Primitive class to encapsulate volumetric data

  Copyright (C) 2008 Marcus D. Hanwell

  This file is part of the Avogadro molecular editor project.
  For more information, see <http://avogadro.sourceforge.net/>

  Avogadro is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  Avogadro is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
  02110-1301, USA.
 **********************************************************************/

#include "mesh.h"

#include <QColor>
#include <QDebug>

namespace Avogadro {

  Mesh::Mesh(QObject *parent) : Primitive(MeshType, parent), m_vertices(0),
    m_normals(0), m_colors(0)
  {
  }

  Mesh::~Mesh()
  {
  }

  const std::vector<Eigen::Vector3f> & Mesh::vertices() const
  {
    return m_vertices;
  }

  const Eigen::Vector3f * Mesh::vertex(int n) const
  {
    return &(m_vertices[n]);
  }

  bool Mesh::setVertices(const std::vector<Eigen::Vector3f> &values)
  {
    m_vertices.clear();
    m_vertices = values;
    return true;
  }

  bool Mesh::addVertices(const std::vector<Eigen::Vector3f> &values)
  {
    if (values.size() % 3 == 0) {
      for (unsigned int i = 0; i < values.size(); ++i) {
        m_vertices.push_back(values.at(i));
      }
      return true;
    }
    else {
      qDebug() << "Error adding vertices." << values.size();
      return false;
    }
  }

  const std::vector<Eigen::Vector3f> & Mesh::normals() const
  {
    return m_normals;
  }

  const Eigen::Vector3f * Mesh::normal(int n) const
  {
    return &(m_normals[n*3]);
  }

  bool Mesh::setNormals(const std::vector<Eigen::Vector3f> &values)
  {
    m_normals.clear();
    m_normals = values;
    return true;
  }

  bool Mesh::addNormals(const std::vector<Eigen::Vector3f> &values)
  {
    if (values.size() % 3 == 0) {
      for (unsigned int i = 0; i < values.size(); ++i) {
        m_normals.push_back(values.at(i));
      }
      return true;
    }
    else {
      qDebug() << "Error adding normals." << values.size();
      return false;
    }
  }

  const std::vector<QColor> & Mesh::colors() const
  {
    return m_colors;
  }

  const QColor * Mesh::color(int n) const
  {
    // If there is only one color return that, otherwise colored by vertex
    if (m_colors.size() == 1) {
      return &(m_colors[0]);
    }
    else {
      return &(m_colors[n*3]);
    }
  }

  bool Mesh::setColors(const std::vector<QColor> &values)
  {
    m_colors.clear();
    m_colors = values;
    return true;
  }

  bool Mesh::addColors(const std::vector<QColor> &values)
  {
    if (values.size() % 3 == 0) {
      for (unsigned int i = 0; i < values.size(); ++i) {
        m_colors.push_back(values.at(i));
      }
      return true;
    }
    else {
      qDebug() << "Error adding colors." << values.size();
      return false;
    }
  }

  bool Mesh::valid() const
  {
    if (m_vertices.size() == m_normals.size()) {
      if (m_colors.size() == 1 || m_colors.size() == m_vertices.size()) {
        return true;
      }
      else {
        return false;
      }
    }
    else {
      return false;
    }
  }

  bool Mesh::clear()
  {
    m_vertices.clear();
    m_normals.clear();
    m_colors.clear();
    return true;
  }

  Mesh& Mesh::operator=(const Mesh& other)
  {
    m_vertices = other.m_vertices;
    m_normals = other.m_vertices;
    m_colors = other.m_colors;
    m_name = other.m_name;
    return *this;
  }

} // End namespace Avogadro

#include "mesh.moc"
