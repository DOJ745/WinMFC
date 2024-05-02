#pragma once
#include <afxlistctrl.h>
class MyCMFCListCtrl : public CMFCListCtrl
{
public:
	virtual int OnCompareItems(LPARAM lParam1, LPARAM lParam2, int nColumn) override
	{
		// Retrieve two comparison items
		CString stritem1, stritem2;
		LVFINDINFO lvfi;
		lvfi.flags = LVFI_PARAM;
		lvfi.lParam = lParam1;
		stritem1 = GetItemText(FindItem(&lvfi), nColumn);
		lvfi.lParam = lParam2;
		stritem2 = GetItemText(FindItem(&lvfi, 0), nColumn);

		// 0th columns are sorted by integer
	/*	if (nColumn == 0)
		{
			int nitem1 = _ttoi(stritem1);
			int nitem2 = _ttoi(stritem2);

			if (nitem1 == nitem2) return 0;
			else return(nitem1 < nitem2 ? -1 : 1);
		}*/
		//else
		//{
			// Compare strings
			int isort = _tcsicmp(stritem1, stritem2);
			return(isort);
		//}
	}
	virtual ~MyCMFCListCtrl() {}
};

