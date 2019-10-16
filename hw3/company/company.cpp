#include "company.hpp"
#include <iostream>
using namespace std;

CompanyTracker::CompanyTracker (int n)
  // initializes the tracker with n students and their 1-person companies
{
  numCompanies = n;
  companies = new Company* [numCompanies];
  for (int i = 0; i < numCompanies; ++i)
      companies[i] = new Company ();
}

CompanyTracker::~CompanyTracker ()
  // deallocates all dynamically allocated memory
{
  // your implementation goes here
  for (int i=0; i<numCompanies; ++i){
    while (largest_company(i) != companies[i]){ // keep deleting until no parent
      split(i); // split function deletes the parent company
    }
  }
  for (int i=0; i<numCompanies; ++i){
    delete companies[i]; // delete each 1 person company
  }
  delete []companies; // delete the array
}

void CompanyTracker::merge (int i, int j)
  /* Merges the largest companies containing students i and j,
     according to the rules described above.
     That is, it generates a new Company object which will
     become the parent company of the largest companies currently
     containing students i and j.
     If i and j already belong to the same company (or are the same),
     merge doesn't do anything.
     If either i or j are out of range, merge doesn't do anything. */
{
  // your implementation goes here
  if ((i>=numCompanies) || (j>=numCompanies) || (i<0)  || (j<0)) {} // out of range
  else if (i == j) {} // i, j are the same
  else if (largest_company(i) != largest_company(j)){ // check if in the same company
    Company* new_merge = new Company(largest_company(i), largest_company(j));
    largest_company(i)->parent = new_merge; // set parent
    largest_company(j)->parent = new_merge; // set parent
  }
}

void CompanyTracker::split (int i)
  /* Splits the largest company that student i belongs to,
     according to the rules described above.
     That is, it deletes that Company object, and makes sure that
     the two subcompanies have no parent afterwards.
     If i's largest company is a 1-person company, split doesn't do anything.
     If i is out of range, split doesn't do anything. */
{
  // your implementation goes here
  Company* temp = largest_company(i);
  if (temp == companies[i]){} // check if it is a 1-person company
  else if ((i >= numCompanies) || (i<0)) {} // out of range
  else{
    temp->merge1->parent = nullptr;
    temp->merge2->parent = nullptr;
    delete temp; // delete parent company
  }
}

bool CompanyTracker::inSameCompany (int i, int j)
  /* Returns whether students i and j are currently in the same company.
     Returns true if i==j.
     Returns false if i or j (or both) is out of range. */
{
  // your implementation goes here
  // out of range
  if ((i>=numCompanies) || (j>=numCompanies) || (i<0)  || (j<0)) return false;
  if (i == j) return true; // i == j
  if (largest_company(i) == largest_company(j)) return true;
  return false;
}

Company* CompanyTracker :: largest_company(int i){
  Company* temp = companies[i]; // first set temp as the smallest company i is in
  while (temp->parent != nullptr) temp = temp-> parent; // find the largest company
  return temp;
}