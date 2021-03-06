///////////////////////////////////////////////////////////////////////////////
/// @file Droite3D.cpp
/// @author DGI
/// @date 2005-06-15
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "Droite3D.h"
#include "Plan3D.h"
#include "Utilitaire.h"


namespace math {


	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn Droite3D::Droite3D(const glm::dvec3& point1, const glm::dvec3& point2)
	///
	/// Constructeur d'une droite 3D � partir de 2 points. \n
	/// Une droite dans l'espace 3d passant par 2 points
	/// @f$  ( P_1, P_2) @f$ est d�finie par l'�quation :
	///
	///  \f[  \frac {x - x_1 } {x_2 - x_1} =  \frac { y - y_1 } {y_2 - y_1} =  \frac { z - z_1 } {z_2 - z_1}    \f]
	/// \n\n
	///
	/// @param[in] point1 : Un point sur la droite.
	/// @param[in] point2 : Un autre point sur la droite (diff�rent du premier
	///                     sinon il y a une lev�e d'exception).
	///
	/// @return Aucune (constructeur).
	///
	///////////////////////////////////////////////////////////////////////////////
	Droite3D::Droite3D(const glm::dvec3& point1, const glm::dvec3& point2)
		: pointDroite_{ point1 }, direction_{ point2 - point1 }
	{
		if (utilitaire::EGAL_ZERO(glm::length(direction_)))
			throw ("Impossible de construire une droite 3d puisque le vecteur de direction est nul.");
	}


	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn bool Droite3D::intersection(const Plan3D& planCoupe, glm::dvec3& intersection)
	///
	/// Cette fonction permet de trouver l'intersection entre une droite et un plan
	/// dans l'espace 3D. La droite ne doit pas �tre parall�le au plan. \n
	///
	///  Si
	///  @f$ a @f$
	///  est diff�rent de z�ro, alors l'intersection est donn�e par :\n
	///
	///   \f[ x = \left ( { \frac {\left ( \frac { ( B  b + C  c)  x_0} {a} - B  y_0 - C  z_0 - D \right)}  { ( A + B \frac  {b} {a} + C \frac{c} {b})} }\right) \f]
	///   \f[ y = \left ( { \frac {\left ( C \frac {c}{b} y_0 - C  z_0 - D \right)}  { ( B + C \frac  {c} {b}) } }\right) \f]
	///   \f[ z = \frac{c} {a} (x - x_0) + z_0  \f]
	///
	///  Si
	///  @f$ b @f$
	///  est diff�rent de z�ro, alors l'intersection est donn�e par :\n
	///
	///   \f[ x = x_0 \f]
	///   \f[ y = \frac{c} {b} (x - x_0) + y_0 \f]
	///   \f[ z = \frac{c} {b} (y - y_0) + z_0  \f]
	///
	///  Sinon, l'intersection est donn�e par :\n
	///
	///   \f[  x = x_0 \f]
	///   \f[  y = y_0 \f]
	///   \f[  z = \frac{(D + A x_0 + B y_0)} {C}   \f]
	///
	///  @param[in]  planCoupe : Le plan avec lequel on veut trouver l'intersection.
	///  @param[out] intersection : Le r�sultat de l'intersection @f$ (s, y, z) @f$ .
	///
	///  @return Faux si la droite est parall�le au plan, donc si donc
	///          l'intersection ne peut �tre trouv�e, vrai autrement.
	///
	///////////////////////////////////////////////////////////////////////////////
	bool Droite3D::intersection(const Plan3D& planCoupe, glm::dvec3& intersection)
	{
		// Initialisation de variables
		const double x0{ pointDroite_[0] };
		const double y0{ pointDroite_[1] };
		const double z0{ pointDroite_[2] };

		const double a{ direction_[0] };
		const double b{ direction_[1] };
		const double c{ direction_[2] };

		double A, B, C, D;
		planCoupe.lireParam(A, B, C, D);

		//Le r�sultat

		// On regarde si le plan et la droite sont parall�les.
		bool bParalleles = utilitaire::EGAL_ZERO(
			glm::dot(planCoupe.lireNormale(), direction_)
			);

		if (!bParalleles) {
			double x = 0, y = 0, z = 0;
			// On doit faire attention aux divisions par 0
			if (!utilitaire::EGAL_ZERO(a)) {
				x = ((B * b + C * c) * x0 / a - B * y0 - C * z0 - D) / (A + B * b / a + C * c / a);
				y = b / a * (x - x0) + y0;
				z = c / a * (x - x0) + z0;
			}
			else if (!utilitaire::EGAL_ZERO(b)) {
				y = (C * c / b * y0 - A * x0 - C * z0 - D) / (B + C * c / b);
				x = x0;
				z = c / b * (y - y0) + z0;
			}
			else {
				x = x0;
				y = y0;
				z = -(D + A * x0 + B * y0) / C;
			}

			intersection[0] = x;
			intersection[1] = y;
			intersection[2] = z;
		}

		return !bParalleles;
	}


	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn bool Droite3D::intersectionSegment( const glm::dvec3& point1, const glm::dvec3& point2)
	///
	/// Cette fonction permet de trouver l'intersection entre un segment de droite
	/// d�fini par 2 points @f$ (P_1, P_2) @f$ et une droite dans l'espace 3D.
	///
	/// @param[in] point1 : Le premier point du segment.
	/// @param[in] point2 : Le deuxi�me point permettant de d�finir le segment de droite.
	///
	/// @return    bool : false => la droite est parall�le au plan,
	///                            donc l'intersection ne peut �tre trouv�e.
	///
	/// @date  2006-02-21  Modification suite aux changements dans Vecteur3
	///
	///////////////////////////////////////////////////////////////////////////////
	bool Droite3D::intersectionSegment(const glm::dvec3& point1,
		const glm::dvec3& point2) const
	{
		glm::dvec3 pointHaut;
		glm::dvec3 pointBas;

		// Si le y n'est pas au niveau du x
		if ((pointDroite_[1] < point1[1]) && (pointDroite_[1] < point2[1])) {
			return false;
		}
		if ((pointDroite_[1] > point1[1]) && (pointDroite_[1] > point2[1])) {
			return false;
		}

		// Si les 2 X sont > ou < que le x du point
		if ((pointDroite_[0] > point1[0]) &&
			(pointDroite_[0] > point2[0])) {
			return false;
		}
		else if ((pointDroite_[0] < point1[0]) &&
			(pointDroite_[0] < point2[0])) {
			return true;
		}

		// Test lorsque le segment croise les deux axes;
		// On trouve les points et on les translate
		if (point1[1] > point2[1]) {
			pointHaut = point1;
			pointBas = point2;
		}
		else {
			pointHaut = point2;
			pointBas = point1;
		}
		pointHaut[0] = pointHaut[0] - pointDroite_[0];
		pointHaut[1] = pointHaut[1] - pointDroite_[1];
		pointBas[0] = pointBas[0] - pointDroite_[0];
		pointBas[1] = pointBas[1] - pointDroite_[1];

		// L'�quation de la droite
		double m{ (pointHaut[1] - pointBas[1]) / (pointHaut[0] - pointBas[0]) };
		double b{ pointHaut[1] - pointHaut[0] * m };

		// Lorsque y = 0
		double x{ (-1.0 * b) / m };

		if (x > 0.0) {
			return true;
		}

		return false;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn double Droite3D::distancePoint( const glm::dvec3& centre )
	///
	/// Calcule la distance euclidienne entre la droite et un point.
	///
	/// @param[in] centre : Point � partir duquel la distance doit �tre calcul�e.
	///
	/// @return Distance du point � la droite.
	///
	////////////////////////////////////////////////////////////////////////
	double Droite3D::distancePoint(const glm::dvec3& centre) const
	{
		// En 2D
		const double ad{ direction_[1] };
		const double bd{ -1.0 * direction_[0] };
		const double cd{ -1.0 * direction_[1] * pointDroite_[0] +
			direction_[0] * pointDroite_[1] };

		double num = fabs(ad * centre[0] + bd * centre[1] + cd);
		double den = sqrt(pow(ad, 2) + pow(bd, 2));

		// En 3D
		const glm::dvec3 centreNul{ centre[0], centre[1], 0.0 };
		const glm::dvec3 vect{ centreNul - pointDroite_ };
		const glm::dvec3 mult{ glm::cross(vect, direction_) };
		num = glm::length(mult);
		den = glm::length(direction_);

		return (num / den);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn glm::dvec3 Droite3D::perpendiculaireDroite(const glm::dvec3& point) const
	///
	/// On trace la perpendicaulaire entre le point et le droite et on trouve
	/// le point d'intersection.
	///
	/// @param[in] point : Un point dans l'espace d'o� est calcul�e la
	///                    perpendiculaire.
	///
	/// @return Le point de rencontre entre la droite et la perpendiculaire.
	///
	////////////////////////////////////////////////////////////////////////
	glm::dvec3 Droite3D::perpendiculaireDroite(const glm::dvec3& point) const
	{
		const glm::dvec3& a{ direction_ };
		const glm::dvec3& p1{ pointDroite_ };
		const glm::dvec3  orig{ 0.0, 0.0, 0.0 };
		const glm::dvec3  op1{ p1 - orig };

		const double op1x{ p1[0] };
		const double op1y{ p1[1] };
		const double op1z{ p1[2] };

		const double op0x{ point[0] };
		const double op0y{ point[1] };
		const double op0z{ point[2] };

		const double ax{ a[0] };
		const double ay{ a[1] };
		const double az{ a[2] };

		const double num{ ax * (op1x - op0x) +
			ay * (op1y - op0y) +
			az * (op1z - op0z) };
		const double den{ -1.0 * (pow(ax, 2) +
			pow(ay, 2) +
			pow(az, 2)) };

		const double r{ num / den };

		const glm::dvec3 oq{ op1 + a * r };

		return oq;
	}


} // Fin de l'espace de nom math.


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
