//////////////////////////////////////////////////////////////////////////////
/// @file FacadeModeleTest.h
/// @author Samuel Millette
/// @date 2015-02-12
/// @version 1.0
///
/// @ingroup Test
//////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_FACADEMODELETEST_H
#define _TESTS_FACADEMODELETEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <memory>

class FacadeModele;
#include "FacadeModele.h"

///////////////////////////////////////////////////////////////////////////
/// @class FacadeModeleTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        m�thodes de la classe FacadeModele.
///
/// @author Samuel Millette
/// @date 2015-02-12
/// @ingroup Test
///////////////////////////////////////////////////////////////////////////
class FacadeModeleTest : public CppUnit::TestFixture
{

	// =================================================================
	// D�claration de la suite de tests et des m�thodes de tests
	//
	// Important, vous devez d�finir chacun de vos cas de tests � l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas ex�cut� !
	// =================================================================
	CPPUNIT_TEST_SUITE(FacadeModeleTest);
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

	/// Cas de test: ...
	void enregistrerXML();


private:

};

#endif // _TESTS_FACADEMODELETEST_H