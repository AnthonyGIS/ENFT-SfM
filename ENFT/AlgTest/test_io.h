#pragma once
#include "stdafx.h"
#include "Viewing/ViewerSequenceSet.h"

class TestIO
{
public:
	TestIO();
	~TestIO();


	static bool IsTrackOutlier(ViewerSequence &viewer, const TrackIndex &iTrk) {
		return !(viewer.m_pSeq->GetTrackState(iTrk) & FLAG_TRACK_STATE_INLIER) ||
			(viewer.m_pSeq->GetTrackState(iTrk) & FLAG_TRACK_STATE_COMMON_OUTLIER);
	}

	static void CheckPoint(ViewerSequence  &viewer)
	{
		const CVD::Rgb<ubyte> clrDefault = CVD::Rgb<ubyte>(COLOR_TRACK_DEFAULT_R, COLOR_TRACK_DEFAULT_G, COLOR_TRACK_DEFAULT_B);
		const TrackIndex nTrks = viewer.m_pSeq->GetPointsNumber();
		string fileName;

		char str_buffer[MAX_LINE_LENGTH];
		fileName = "..//output//1_new.txt";
		ofstream fout(fileName);
		
		fout << "# points of generate." << endl<<"# totall points ( outlier include):"<< nTrks <<endl;
		for (TrackIndex iTrk = 0; iTrk < nTrks; ++iTrk) {
			if (!(viewer.m_pSeq->GetTrackState(iTrk) & FLAG_TRACK_STATE_SOLVED) ||
				IsTrackOutlier(viewer,iTrk))
				continue;
			const CVD::Rgb<ubyte> &clr = iTrk < viewer.m_pSeq->GetTrackColorsNumber() ? viewer.m_pSeq->GetTrackColor(iTrk) : clrDefault;
			
			//fout << str_buffer;

			Point3D pt_tmp = viewer.m_pSeq->GetPoint(iTrk);
			fout << pt_tmp.X()<< "," << pt_tmp.Y()<< ","<< pt_tmp.Z()<< ",";

			sprintf(str_buffer, "%d,%d,%d", clr.red,clr.green, clr.blue);
			fout << str_buffer << endl;
		}
		
		fout.close();
		
		sprintf(str_buffer, "Saved \'%s\'\n", fileName);
		cout << str_buffer << endl;
	}







private:

};

TestIO::TestIO()
{
}

TestIO::~TestIO()
{
}