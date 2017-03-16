/**
*	created:		2013-4-12   17:43
*	filename: 		FKPageControl
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKBase.h"
#include "FKButton.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		class FK_EXPORT PageControl : public Base
		{
				static const unsigned int MaxPages = 64;

				FK_CONTROL( PageControl, Base );

				virtual void SetPageCount( unsigned int i );
				virtual unsigned int GetPageCount() { return m_iPages; }

				virtual void ShowPage( unsigned int i );
				virtual unsigned int GetPageNumber() { return m_iCurrentPage; }
				virtual Controls::Base* GetPage( unsigned int i );
				virtual Controls::Base* GetCurrentPage();

				virtual void NextPage();
				virtual void PreviousPage();
				virtual void Finish();

				Controls::Button* NextButton() { return m_Next; }
				Controls::Button* BackButton() { return m_Back; }
				Controls::Button* FinishButton() { return m_Finish; }
				Controls::Label* Label() { return m_Label; }

				void SetUseFinishButton( bool b ) { m_bFinish = b; }
				bool GetUseFinishButton() { return m_bFinish; }

				Event::Caller	onPageChanged;
				Event::Caller	onFinish;

			protected:

				virtual void HideAll();

				unsigned int			m_iCurrentPage;
				unsigned int			m_iPages;
				Controls::Base*			m_pPages[MaxPages];

				Controls::Button*		m_Next;
				Controls::Button*		m_Back;
				Controls::Button*		m_Finish;
				Controls::Label*		m_Label;

				bool					m_bFinish;

		};

	}
}
//------------------------------------------------------------------------