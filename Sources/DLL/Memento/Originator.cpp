#include "Originator.h"


Originator::Originator()
{
	historique_ = new CareTaker();
	position_ = 0;
}

Originator::~Originator()
{
	delete historique_;

	arbreActuel_ = nullptr;
	historique_ = nullptr;
}

void Originator::annuler()
{
	// Ne rien faire lorsque qu'il n'y a pas eu de modification
	if (position_ == 0)
		return;

	// Ne rien faire lorsqu'il n'y a pas d'historique
	if (historique_->size() == 0)
		return;

	// Tenter d'obtenir l'element de sauvegarde precedent
	if (historique_->obtenirMemento(position_ - 1) == nullptr)
		return;

	// Obtenir la sauvegarde desiree
	std::map<int, NoeudAbstrait*> sauvegarde;
	sauvegarde = historique_->obtenirMemento(position_ - 1)->obtenirSauvegarde();

	NoeudAbstrait* temp;
	std::map<int, NoeudAbstrait*>::iterator iter;

	// Modifier l'arbre courant avec les informations de sauvegarde
	for (iter = sauvegarde.begin(); iter != sauvegarde.end(); iter++)
	{
		temp = arbreActuel_->obtenirNoeudSelonNumero(iter->first);

		if (temp != nullptr)
		{
			temp->assignerPositionRelative(iter->second->obtenirPositionRelative());
			temp->assignerEchelle(iter->second->obtenirAgrandissement());
			temp->assignerRotationHard(iter->second->obtenirRotation());
			temp->setColorShift(iter->second->getColorShift());
		}

		temp = nullptr;
	}



	// Position courante dans l'historique change
	position_--;
}

void Originator::retablir()
{
	// Ne rien faire lorsqu'il n'y a pas eu d'autres modifications
	if (position_ == historique_->size() - 1)
		return;

	// Ne rien faire lorsqu'il n'y a pas d'historique
	if (historique_->size() == 0)
		return;

	// Tenter d'obtenir l'element de sauvegarde suivant
	if (historique_->obtenirMemento(position_ + 1) == nullptr)
		return;
	
	// Obtenir la sauvegarde desiree
	std::map<int, NoeudAbstrait*> sauvegarde;
	sauvegarde = historique_->obtenirMemento(position_ + 1)->obtenirSauvegarde();

	NoeudAbstrait* temp;
	std::map<int, NoeudAbstrait*>::iterator iter;

	// Modifier l'arbre courant avec les informations de sauvegarde
	for (iter = sauvegarde.begin(); iter != sauvegarde.end(); iter++)
	{
		temp = arbreActuel_->obtenirNoeudSelonNumero(iter->first);

		if (temp != nullptr)
		{
			temp->assignerPositionRelative(iter->second->obtenirPositionRelative());
			temp->assignerEchelle(iter->second->obtenirAgrandissement());
			temp->assignerRotationHard(iter->second->obtenirRotation());
			temp->setColorShift(iter->second->getColorShift());
		}
	}

	// Position courante dans l'historique change
	position_++;

}

void Originator::sauvegarder()
{
	// La sauvegarde courante est deja la derniere sauvegarde
	if (position_ + 1 == historique_->size())
	{
		if(!(historique_->ajouter(new Memento(arbreActuel_))))
			position_++;
	}

	// On est au debut
	else if (position_ == 0)
	{
		historique_->vider();
		historique_->ajouter(new Memento(arbreActuel_));
	}

	// On est au milieu
	else
	{
		historique_->ecraser(position_);
		historique_->ajouter(new Memento(arbreActuel_));
		position_++;
	}
	
}