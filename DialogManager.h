#pragma once
#include "ProjectDialog.h"
#include "ThreeTunnelDlg.h"
#include "MethodChooseDialog.h"
#include "TheoreticalDialog.h"
#include "ExperienceDialog.h"
#include "LooseRangeDialog.h"
#include "ParametersDialog.h"
class DialogManager
{
public:
	DialogManager(const DialogManager&) = delete;
	DialogManager& operator=(const DialogManager&) = delete;
	static DialogManager& GetInstance() {
		static DialogManager instance;
		return instance;
	};


	static DialogManager& RenewInstance() {
		static DialogManager instance;
		return instance;
	};



	~DialogManager()
	{
		delete mProjectDlg;
		delete mTunnelChooseDlg;
		delete mMethodChooseDlg;
		delete mTheoryDlg;
		delete mExpDlg;
		delete mLooseDlg;
		delete mResultDlg;
	};

	void ShowProjectDialog() {
		if (hasCurrentFile == true)
		{
			mProjectDlg->UpdateUI();
		}
		mProjectDlg->ShowWindow(SW_SHOW);

	};
	void HideProjectDialog() {
		mProjectDlg->ShowWindow(SW_HIDE);
	};
	
	void ShowTunnelChooseDlg() {
		if (hasCurrentFile == true)
		{
			mTunnelChooseDlg->UpdateUI();
		}
		mTunnelChooseDlg->ShowWindow(SW_SHOW);
	};

	void HideTunnelChooseDlg() {
		mTunnelChooseDlg->ShowWindow(SW_HIDE);
	};

	void ShowMethodChooseDlg() {
		if (hasCurrentFile == true)
		{
			mMethodChooseDlg->UpdateUI();
		}
		mMethodChooseDlg->ShowWindow(SW_SHOW);
	};

	void HideMethodChooseDlg() {
		mMethodChooseDlg->ShowWindow(SW_HIDE);
	};

	void ShowTheoryDlg() {
		if (hasCurrentFile == true)
		{
			mTheoryDlg->UpdateUI();
		}
		mTheoryDlg->ShowWindow(SW_SHOW);
	};

	void HideTheoryDlg() {
		mTheoryDlg->ShowWindow(SW_HIDE);
	};

	void ShowExpDlg() {
		if (hasCurrentFile == true)
		{
			mExpDlg->UpdateUI();
		}
		mExpDlg->ShowWindow(SW_SHOW);
	};

	void HideExpDlg() {
		mExpDlg->ShowWindow(SW_HIDE);
	};

	void ShowLooseDlg() {
		if (hasCurrentFile == true)
		{
			mLooseDlg->UpdateUI();
		}
		mLooseDlg->ShowWindow(SW_SHOW);
	};
	void HideLooseDlg() {
		mLooseDlg->ShowWindow(SW_HIDE);
	};

	

	void ShowResultDlg() {
		
		if (hasCurrentFile == true || hasCalculated == true)
		{
			mResultDlg->UpdateUI();
		}
		mResultDlg->ShowWindow(SW_SHOW);
	};
	void HideResultDlg() {
		mResultDlg->ShowWindow(SW_HIDE);
	};

	bool getHasCurrentFile() const {
		return hasCurrentFile;
	};
	void setHasCurrentFile(bool value) {
		hasCurrentFile = value;
	};

	bool getHasCalculated() const {
		return hasCalculated;
	};
	void setHasCalculated(bool value) {
		hasCalculated = value;
	};

private:


	DialogManager()
	{
		mProjectDlg = new CProjectDialog();
		mProjectDlg->Create(IDD_PROJECT_DIALOG, 0);
		mTunnelChooseDlg = new CThreeTunnelDlg();
		mTunnelChooseDlg->Create(IDD_THREE_TUNNEL_DIALOG, 0);
		mMethodChooseDlg = new CMethodChooseDialog();
		mMethodChooseDlg->Create(IDD_METHOD_CHOOSE_DIALOG, 0);
		mTheoryDlg = new CTheoreticalDialog();
		mTheoryDlg->Create(IDD_THEORETICAL_CALCULATION_DIALOG, 0);
		mExpDlg = new CExperienceDialog();
		mExpDlg->Create(IDD_PROGRAM_EXPERIENCE_DIALOG, 0);
		mLooseDlg = new CLooseRangeDialog();
		mLooseDlg->Create(IDD_LOOSE_RANGE_DIALOG, 0);
		mResultDlg = new CParametersDialog();
		mResultDlg->Create(IDD_PARAMETERS_DIALOG, 0);
	}

	CProjectDialog *mProjectDlg;
	CThreeTunnelDlg *mTunnelChooseDlg;
	CMethodChooseDialog *mMethodChooseDlg;
	CTheoreticalDialog *mTheoryDlg;
	CExperienceDialog *mExpDlg;
	CLooseRangeDialog *mLooseDlg;
	CParametersDialog *mResultDlg;

	bool hasCurrentFile = false;
	bool hasCalculated = false;
};

