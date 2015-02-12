//////////////////////////////////////////////////////////////////////////////
/// @file ArbreRenduINF2990Test.h
/// @author Samuel Millette
/// @date 2015-02-12
/// @version 1.0
///
/// @ingroup Test
//////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_ARBRERENDUINF2990TEST_H
#define _TESTS_ARBRERENDUINF2990TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <memory>

class ArbreRenduINF2990;
#include "ArbreRenduINF2990.h"

///////////////////////////////////////////////////////////////////////////
/// @class ArbreRenduINF2990Test
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        m�thodes de la classe ArbreRenduINF2990.
///
/// @author Samuel Millette
/// @date 2015-02-12
/// @ingroup Test
///////////////////////////////////////////////////////////////////////////
class ArbreRenduINF2990Test : public CppUnit::TestFixture
{

	// =================================================================
	// D�claration de la suite de tests et des m�thodes de tests
	//
	// Important, vous devez d�finir chacun de vos cas de tests � l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas ex�cut� !
	// =================================================================
	CPPUNIT_TEST_SUITE(ArbreRenduINF2990Test);
	CPPUNIT_TEST(testArbreDefaut);
	CPPUNIT_TEST(testXmlInexistant);
	CPPUNIT_TEST(testPortails);
	CPPUNIT_TEST(creerNoeudParUsine);
	CPPUNIT_TEST(boiteEnglobante);
	CPPUNIT_TEST(assignerDefault);
	CPPUNIT_TEST_SUITE_END();

public:

	// =================================================================
	// M�thodes pour initialiser et 'finaliser' la suite de tests
	// =================================================================

	/// Traitement � effectuer pour initialiser cette suite de tests
	void setUp();

	/// Traitement � effectuer pour 'finaliser' cette suite de tests
	void tearDown();


	// =================================================================
	// D�finissez ici les diff�rents cas de tests...
	// =================================================================

	/// Cas de test: Initialiser l'arbre par d�faut.
	void testArbreDefaut();

	/// Cas de test: Le fichier XML charg� est n'existe pas.
	void testXmlInexistant();

	/// Cas de test: Deux portails sont li�s lorsque cr��s.
	void testPortails();

	/// Cas de test: Cr�er un noeud de type inexistant.
	void creerNoeudParUsine();

	/// Cas de test: Test bo�te englobante.
	void boiteEnglobante();

	/// Cas de test: Assigner une position relative qui change le default layout.
	void assignerDefault();

private:
	/// Instance d'un arbre
	std::unique_ptr<ArbreRenduINF2990> arbre;
};

#endif // _TESTS_ARBRERENDUINF2990_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
