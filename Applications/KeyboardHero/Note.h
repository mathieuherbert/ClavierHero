/*
 * Note.h
 *
 *  Created on: 20 oct. 2013
 *      Author: Julien Deray, Mathieu Cartaud, Mathieu Herbert
 */

#ifndef NOTE_H_
#define NOTE_H_

#include "model/Hauteur.h"
#include "drivers/EcranV.h"
#include "model/Puls.h"
#include "model/Octave.h"
#include "model/Touche.h"
#include "lib/String.h"
#include "ClavierHero.h"
#include <sextant/Activite/Threads.h>
#include "sextant/types.h"

class Note : public Threads {
private:
	Puls *temps;	// Croche, Noire, ...
    int hauteur;	// DO, RE, MI, ...
    int touche;		// F1, F2,  ... -> touche qu'il faudra appuyer pour gagner des points
    int octave;		// Num�ro de l'octave
    EcranV *ecran;
    Timer *timer;
    int m_tempo;
    int getToucheCol();
    void verificationDeValidationColUn(int & col, int & ligne);
    void verificationDeValidationColDeux(int & col, int & ligne);
    void verificationDeValidationColTrois(int & col, int & ligne);
    void verificationDeValidationColQuatre(int & col, int & ligne);
    Couleur getCouleur(int col);
public:
    int duree;
    Note(Puls *temps, int hauteur, int touche, int octave, EcranV *ecran, Timer *timer);
    void run();
    Puls *getTempsNum();
    int getFrequence();
    int getHauteur();
    int getOctave();
    void setDiese();
    void setIcon(int ligne);
    void eraseIcon();
    void run(int vitesseDefilement);
};


#endif /* NOTE_H_ */
