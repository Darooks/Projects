#ifndef _DLL_H_
#define _DLL_H_

#if BUILDING_DLL
# define DLLIMPORT __declspec (dllexport)
#else /* Not BUILDING_DLL */
# define DLLIMPORT __declspec (dllimport)
#endif /* Not BUILDING_DLL */

class DLLIMPORT DllClass
{
public:
	DllClass();
	virtual ~DllClass(void);
	void show_everything(pierscien* pierwszy);
	pierscien usun(pierscien *root, int hash);
	void show(pierscien* pierwszy, int hash);
	int hashuj(char *tab);
	pierscien insert(pierscien *root, char *tab);

private:

};

#endif /* _DLL_H_ */