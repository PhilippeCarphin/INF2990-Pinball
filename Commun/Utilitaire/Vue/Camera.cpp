///////////////////////////////////////////////////////////////////////////////
/// @file Camera.cpp
/// @author DGI
/// @date 2006-12-15
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
///////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <GL/glu.h>
#include "Utilitaire.h"
#include "Camera.h"
#include <iostream>
#include "../Utilitaire.h"
#include "../../Sources/DLL/Application/FacadeModele.h"
//#include "../../Sources/DLL/Text/ControleurTexte.h"


namespace vue {


	////////////////////////////////////////////////////////////////////////////
	///
	/// @fn Camera::Camera(const glm::dvec3& position, const glm::dvec3& pointVise, const glm::dvec3& directionHautCamera, const glm::dvec3& directionHautMonde)
	///
	/// Constructeur de la cam�ra � partir des coordonn�es cart�siennes.
	///
	/// @param[in]  position            : position de la cam�ra.
	/// @param[in]  pointVise           : point vis�.
	/// @param[in]  directionHautCamera : direction du haut de la cam�ra.
	/// @param[in]  directionHautMonde  : direction du haut du monde de la
	///                                   cam�ra.
	///
	/// @return Aucune (constructeur).
	///
	////////////////////////////////////////////////////////////////////////////
	Camera::Camera(const glm::dvec3& position,
		const glm::dvec3& pointVise,
		const glm::dvec3& directionHautCamera,
		const glm::dvec3& directionHautMonde,
		float angleTheta,
		float anglePhi
		)
		: position_{ position },
		pointVise_{ pointVise },
		directionHaut_{ directionHautCamera },
		directionHautMonde_{ directionHautMonde },
		theta_{angleTheta},
		phi_{anglePhi},
		dist_{position.z}
	{		
	}


	////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Camera::deplacerXY( double deplacementX, double deplacementY )
	///
	/// D�place la cam�ra dans le plan perpendiculaire � la direction vis�e
	///
	/// @param[in]  deplacementX : D�placement sur l'axe horizontal du plan de
	///                            la cam�ra.
	/// @param[in]  deplacementY : D�placement sur l'axe vertical du plan de la
	///                            cam�ra.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////////
	void Camera::deplacerXY(double deplacementX, double deplacementY)
	{
	}


	////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Camera::deplacerZ( double deplacement, bool bougePointVise )
	///
	/// D�place la cam�ra dans l'axe de la direction vis�e.
	///
	/// @param[in]  deplacement    : D�placement sur l'axe de la direction vis�e
	/// @param[in]  bougePointVise : Si vrai, le point de vis� est �galement
	///                              d�plac�.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////////
	void Camera::deplacerZ(double deplacement, bool bougePointVise)
	{
		/*TODO : Tenir du bougePointVise*/
		this->position_.z += deplacement;
	}


	////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Camera::tournerXY( double rotationX, double rotationY, bool empecheInversion )
	///
	/// Rotation de la cam�ra autour de sa position (et donc d�placement du
	/// point vis� en gardant la position fixe.
	///
	/// @param[in] rotationX        : Modification de l'angle de rotation du
	///                               point vis� par rapport � la position.
	/// @param[in] rotationY        : Modification de l'angle d'�l�vation du
	///                               point vis� par rapport � la position.
	/// @param[in] empecheInversion : Si vrai, la rotation n'est pas effectu�e
	///                               si elle am�nerait une inversion de la
	///                               cam�ra.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////////
	void Camera::tournerXY(double rotationX,
		double rotationY,
		bool   empecheInversion //=true
		)
	{
	}


	//#define SHOW_OUTPUT 1
	////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Camera::orbiterXY( double rotationX, double rotationY, bool empecheInversion )
	///
	/// Rotation de la cam�ra autour de son point de vis� (et donc d�placement
	/// de la position en gardant le point de vis� fixe.
	///
	/// @param[in]  rotationX        : Modification de l'angle de rotation de la
	///                                position par rapport au point de vis�.
	/// @param[in]  rotationY        : Modification de l'angle d'�l�vation de la
	///                                position par rapport au point de vis�.
	/// @param[in]  empecheInversion : Si vrai, la rotation n'est pas effectu�
	///                                si elle am�nerait une inversion de la
	///                                cam�ra.
	///
	///  @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////////
	void Camera::orbiterXY(double rotationX,
		double rotationY,
		bool   empecheInversion //=true
		)
	{
		if (empecheInversion)
			return;
		/* Les angles doivent �tre en radian*/
		double dist = glm::distance(position_, pointVise_);
		
		double deltaTheta = utilitaire::SIGN(rotationX) * utilitaire::DEG_TO_RAD(abs(rotationX));
		double deltaPhi   = utilitaire::SIGN(rotationY) * utilitaire::DEG_TO_RAD(abs(rotationY));
	
		/*std::string ancienTexte;
		std::string informationAngle = "Phi | Theta" + std::to_string(theta_)
			+ " | " + std::to_string(phi_) + " \n";
		FacadeModele::obtenirInstance()->obtenircontroleurTexte()->updateText(ancienTexte, );*/
#ifdef SHOW_OUTPUT
		std::cout << "RECU --- deltaPhi | deltaTheta" + std::to_string(deltaPhi)
			+ " | " + std::to_string(deltaTheta) + " \n";
		std::cout << "Distance : " << dist << std::endl;
#endif
		// Assignation des nouveaux angles
		theta_ += deltaTheta;
		phi_ += deltaPhi;

		// On s'assure de ne pas d�passer certains angles
		clampAngles();
#ifdef SHOW_OUTPUT		
		std::cout << "Nouveau Phi | Theta" + std::to_string(phi_)
			+ " | " + std::to_string(theta_) + " \n";
#endif
		// On calcule la bonne position en fonction des angles 
		calculerPositionOrbite();
		positionnerOrbite();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Camera::positionnerOrbite() const
	///
	/// Positionne la cam�ra dans la sc�ne � l'aide de gluLookAt().
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void Camera::positionnerOrbite() const
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		//	gluLookAt(position_[0], position_[1], position_[2],
		//		pointVise_[0], pointVise_[1], pointVise_[2],
		//		directionHaut_[0], directionHaut_[1], directionHaut_[2]);
		glPushMatrix();
		glRotated(180.0 / 3.1415 * phi_ - 90.0, 1.0, 0.0, 0.0);
		glRotated(180.0 / 3.1415 * theta_, 0.0, 0.0, 1.0);
		FacadeModele::obtenirInstance()->dessinerSkybox();
		glPopMatrix();

		glTranslated(0.0, 0.0, -dist_);
		glRotated(180.0 / 3.1415 * phi_ - 90.0, 1.0, 0.0, 0.0);
		glRotated(180.0 / 3.1415 * theta_, 0.0, 0.0, 1.0);
		glTranslated(-pointVise_.x, -pointVise_.y, 0.0);
	}

	void Camera::calculerPositionOrbite()
	{
		//gluLookAt( dist*cos(theta)*sin(phi), dist*sin(theta)*sin(phi), dist*cos(phi),   <--- TP3 INF2705
		//gluLookAt( dist*sin(phi)*sin(theta), dist*cos(phi), dist*sin(phi)*cos(theta), 0, 1, 0, 0, 2, 0 ); <---TP4 INF2705
#if 1 /* Version du TP3*/
		position_.x = dist_ * sin(phi_) * sin(theta_);
		position_.y = dist_ * cos(phi_);
		position_.z = dist_ * sin(phi_) * cos(theta_);
#else /*Version du TP4*/
		position_.x = dist_ * sin(phi_) * sin(theta_);
		position_.y = dist_ * cos(phi_);
		position_.z = dist_ * sin(phi_) * cos(theta_);
#endif

	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Camera::positionnerOrbite() const
	///
	/// Positionne la cam�ra dans la sc�ne � l'aide de gluLookAt().
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void Camera::positionnerOrtho() const
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		FacadeModele::obtenirInstance()->dessinerSkybox();
		gluLookAt(position_[0], position_[1], position_[2],
			pointVise_[0], pointVise_[1], pointVise_[2],
			directionHaut_[0], directionHaut_[1], directionHaut_[2]);

	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Camera::clampAngles() 
	///
	/// Ajuste la valeur des angles pour qu'elle ne d�passe pas un certain 
	/// angle. Ceci est fait pour �viter de voir l'arri�re de la zone de jeu
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void Camera::clampAngles()
	{
		if (phi_ >= (utilitaire::PI/2.0))
		{
#ifdef SHOW_OUTPUT
			std::cout << "Angle phi trop grand : on le remet � PI \n";
#endif
			phi_ = (utilitaire::PI/2.0) - 0.0001;
		}
		else if (phi_ <= (utilitaire::PI/6.0))
		{
#ifdef SHOW_OUTPUT
			std::cout << "Angle phi trop petit : on le remet � 0 \n";
#endif
			phi_ = (utilitaire::PI/6.0) +0.0001;
		}
		if (theta_ >= utilitaire::PI / 2.0)
		{
#ifdef SHOW_OUTPUT
			std::cout << "Angle theta trop grand : on le remet � PI \n";
#endif
			theta_ = (utilitaire::PI / 2.0) - 0.0001;
		}
		else if (theta_ <= -utilitaire::PI / 2.0)
		{
#ifdef SHOW_OUTPUT
			std::cout << "Angle theta trop petit : on le remet � 0 \n";
#endif
			theta_ = -(utilitaire::PI / 2.0) + 0.0001;
		}
	}

}; // Fin du namespace vue.


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
