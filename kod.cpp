void GINPUT::KEYBOARD(void)
{
	int v1;
	int v2;
	float v3;
	float v4;
	float v5;
	float v6;
	float v7;
	float v8;
	float v9;
	float v10;
	float v11;
	float v12;
	float v13;
	float a2;
	int v15;
	D3DXVECTOR3 v17;
	int i;
	D3DXMATRIX v21;

	if (mMAIN->mMainMode != 6 || mMAIN->mSubMode != 4)
		return;
	if (!mEDITBOX->mDataIndex)
	{
		if (mMYINFO->mZoneAvatarInfo.aVisibleState || !mINPUT->mCheckCameraRecord)
		{
			if ((mGXD->mKeyboardImmediateData[30] & 0x80) != 0)
			{
				mGXD->ChangeCameraForHorizon(6.0);
				return;
			}
			if ((mGXD->mKeyboardImmediateData[32] & 0x80) != 0)
			{
				mGXD->ChangeCameraForHorizon(-6.0);
				return;
			}
			goto LABEL_73;
		}
		v15 = mINPUT->mCameraRecordState;
		if (v15 == 1)
		{
			if ((mGXD->mKeyboardImmediateData[17] & 0x80) != 0)
			{
				if (mMYINFO->mMoveZoneState)
					return;
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0] = mINPUT->mCameraRecordSpeed[0] * mGXD->mCameraForward.x
					+ mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0];
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[1] = mINPUT->mCameraRecordSpeed[0] * mGXD->mCameraForward.y
					+ mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[1];
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[2] = mINPUT->mCameraRecordSpeed[0] * mGXD->mCameraForward.z
					+ mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[2];
				mPROCESSDATA->PROCESS_FOR_DATA_507(&mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0]);
			}
			else if ((mGXD->mKeyboardImmediateData[31] & 0x80) != 0)
			{
				if (mMYINFO->mMoveZoneState)
					return;
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0] = mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0]
					- mINPUT->mCameraRecordSpeed[0] * mGXD->mCameraForward.x;
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[1] = mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[1]
					- mINPUT->mCameraRecordSpeed[0] * mGXD->mCameraForward.y;
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[2] = mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[2]
					- mINPUT->mCameraRecordSpeed[0] * mGXD->mCameraForward.z;
				mPROCESSDATA->PROCESS_FOR_DATA_507(&mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0]);
			}
			else if ((mGXD->mKeyboardImmediateData[30] & 0x80) != 0)
			{
				a2 = mINPUT->mCameraRecordSpeed[1] * -1.0;
				mGXD->ChangeCameraForHorizon(a2);
			}
			else if ((mGXD->mKeyboardImmediateData[32] & 0x80) != 0)
			{
				v13 = mINPUT->mCameraRecordSpeed[1] * 1.0;
				mGXD->ChangeCameraForHorizon(v13);
			}
			else if ((mGXD->mKeyboardImmediateData[16] & 0x80) != 0)
			{
				if (mMYINFO->mMoveZoneState)
					return;
				v17.x = mGXD->mCameraForward.x;
				v17.y = 0.0;
				v17.z = mGXD->mCameraForward.z;
				D3DXVec3Normalize(&v17, &v17);
				D3DXMatrixRotationY(&v21, 1.5707964);
				D3DXVec3TransformNormal(&v17, &v17, &v21);
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0] = mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0] - mINPUT->mCameraRecordSpeed[2] * v17.x;
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[1] = mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[1] - mINPUT->mCameraRecordSpeed[2] * v17.y;
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[2] = mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[2] - mINPUT->mCameraRecordSpeed[2] * v17.z;
				mPROCESSDATA->PROCESS_FOR_DATA_507(&mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0]);
			}
			else if ((mGXD->mKeyboardImmediateData[18] & 0x80) != 0)
			{
				if (mMYINFO->mMoveZoneState)
					return;
				v17.x = mGXD->mCameraForward.x;
				v17.y = 0.0;
				v17.z = mGXD->mCameraForward.z;
				D3DXVec3Normalize(&v17, &v17);
				D3DXMatrixRotationY(&v21, 1.5707964);
				D3DXVec3TransformNormal(&v17, &v17, &v21);
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0] = mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0] + mINPUT->mCameraRecordSpeed[2] * v17.x;
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[1] = mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[1] + mINPUT->mCameraRecordSpeed[2] * v17.y;
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[2] = mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[2] + mINPUT->mCameraRecordSpeed[2] * v17.z;
				mPROCESSDATA->PROCESS_FOR_DATA_507(&mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0]);
			}
			else if ((mGXD->mKeyboardImmediateData[19] & 0x80) != 0)
			{
				if (mMYINFO->mMoveZoneState)
					return;
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[1] = mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[1] + mINPUT->mCameraRecordSpeed[3];
				mPROCESSDATA->PROCESS_FOR_DATA_507(&mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0]);
			}
			else if ((mGXD->mKeyboardImmediateData[33] & 0x80) != 0)
			{
				if (mMYINFO->mMoveZoneState)
					return;
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[1] = mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[1] - mINPUT->mCameraRecordSpeed[3];
				mPROCESSDATA->PROCESS_FOR_DATA_507(&mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0]);
			}
			goto LABEL_73;
		}
		if (v15 != 2)
		{
			if (v15 != 3)
				goto LABEL_73;
			if ((mGXD->mKeyboardImmediateData[17] & 0x80) != 0)
			{
				v7 = mINPUT->mCameraRecordSpeed[0] * 0.1;
				mGXD->ChangeCameraForForward(v7);
				mINPUT->mPostCameraLength = mUTIL.ReturnLengthXYZ( &mGXD->mCameraEye.x, &mGXD->mCameraLook.x);
				if (mINPUT->mPostCameraLength < 10.0)
				{
					v6 = mINPUT->mCameraRecordSpeed[0] * -0.1;
					mGXD->ChangeCameraForForward(v6);
					mINPUT->mPostCameraLength = mUTIL.ReturnLengthXYZ( &mGXD->mCameraEye.x, &mGXD->mCameraLook.x);
				}
				goto LABEL_73;
			}
			if ((mGXD->mKeyboardImmediateData[31] & 0x80) != 0)
			{
				v5 = mINPUT->mCameraRecordSpeed[0] * -0.1;
				mGXD->ChangeCameraForForward(v5);
				mINPUT->mPostCameraLength = mUTIL.ReturnLengthXYZ( &mGXD->mCameraEye.x, &mGXD->mCameraLook.x);
				goto LABEL_73;
			}
			if ((mGXD->mKeyboardImmediateData[30] & 0x80) != 0)
			{
				v4 = mINPUT->mCameraRecordSpeed[1] * -1.0;
				mGXD->ChangeCameraForHorizon(v4);
				goto LABEL_73;
			}
			if ((mGXD->mKeyboardImmediateData[32] & 0x80) != 0)
			{
				v3 = mINPUT->mCameraRecordSpeed[1] * 1.0;
				mGXD->ChangeCameraForHorizon(v3);
				goto LABEL_73;
			}
			if ((mGXD->mKeyboardImmediateData[16] & 0x80) == 0)
			{
				if ((mGXD->mKeyboardImmediateData[18] & 0x80) == 0)
				{
					if ((mGXD->mKeyboardImmediateData[19] & 0x80) == 0)
					{
						if ((mGXD->mKeyboardImmediateData[33] & 0x80) != 0)
						{
							mGXD->mCameraEye.y = mGXD->mCameraEye.y - mINPUT->mCameraRecordSpeed[3];
							mGXD->SetCameraPosition(

								mGXD->mCameraEye.x,
								mGXD->mCameraEye.y,
								mGXD->mCameraEye.z,
								mGXD->mCameraLook.x,
								mGXD->mCameraLook.y,
								mGXD->mCameraLook.z);
							mTW2AddIn->SetCameraPosition(								
								mGXD->mCameraEye.x,
								mGXD->mCameraEye.y,
								mGXD->mCameraEye.z,
								mGXD->mCameraLook.x,
								mGXD->mCameraLook.y,
								mGXD->mCameraLook.z);
							mINPUT->mPostCameraLength = mUTIL.ReturnLengthXYZ( &mGXD->mCameraEye.x, &mGXD->mCameraLook.x);
						}
						goto LABEL_73;
					}
					goto LABEL_49;
				}
			LABEL_47:
				v17.x = mGXD->mCameraForward.x;
				v17.y = 0.0;
				v17.z = mGXD->mCameraForward.z;
				D3DXVec3Normalize(&v17, &v17);
				D3DXMatrixRotationY(&v21, 1.5707964);
				D3DXVec3TransformNormal(&v17, &v17, &v21);
				mGXD->mCameraEye.x = mINPUT->mCameraRecordSpeed[2] * 0.1 * v17.x + mGXD->mCameraEye.x;
				mGXD->mCameraEye.y = mINPUT->mCameraRecordSpeed[2] * 0.1 * v17.y + mGXD->mCameraEye.y;
				mGXD->mCameraEye.z = mINPUT->mCameraRecordSpeed[2] * 0.1 * v17.z + mGXD->mCameraEye.z;
				mGXD->SetCameraPosition(

					mGXD->mCameraEye.x,
					mGXD->mCameraEye.y,
					mGXD->mCameraEye.z,
					mGXD->mCameraLook.x,
					mGXD->mCameraLook.y,
					mGXD->mCameraLook.z);
				mTW2AddIn->SetCameraPosition(
					
					mGXD->mCameraEye.x,
					mGXD->mCameraEye.y,
					mGXD->mCameraEye.z,
					mGXD->mCameraLook.x,
					mGXD->mCameraLook.y,
					mGXD->mCameraLook.z);
				mINPUT->mPostCameraLength = mUTIL.ReturnLengthXYZ( &mGXD->mCameraEye.x, &mGXD->mCameraLook.x);
				goto LABEL_73;
			}
		LABEL_45:
			v17.x = mGXD->mCameraForward.x;
			v17.y = 0.0;
			v17.z = mGXD->mCameraForward.z;
			D3DXVec3Normalize(&v17, &v17);
			D3DXMatrixRotationY(&v21, 1.5707964);
			D3DXVec3TransformNormal(&v17, &v17, &v21);
			mGXD->mCameraEye.x = mGXD->mCameraEye.x - mINPUT->mCameraRecordSpeed[2] * 0.1 * v17.x;
			mGXD->mCameraEye.y = mGXD->mCameraEye.y - mINPUT->mCameraRecordSpeed[2] * 0.1 * v17.y;
			mGXD->mCameraEye.z = mGXD->mCameraEye.z - mINPUT->mCameraRecordSpeed[2] * 0.1 * v17.z;
			mGXD->SetCameraPosition(

				mGXD->mCameraEye.x,
				mGXD->mCameraEye.y,
				mGXD->mCameraEye.z,
				mGXD->mCameraLook.x,
				mGXD->mCameraLook.y,
				mGXD->mCameraLook.z);
			mTW2AddIn->SetCameraPosition(
				
				mGXD->mCameraEye.x,
				mGXD->mCameraEye.y,
				mGXD->mCameraEye.z,
				mGXD->mCameraLook.x,
				mGXD->mCameraLook.y,
				mGXD->mCameraLook.z);
			mINPUT->mPostCameraLength = mUTIL.ReturnLengthXYZ( &mGXD->mCameraEye.x, &mGXD->mCameraLook.x);
			goto LABEL_73;
		}
		if ((mGXD->mKeyboardImmediateData[17] & 0x80) != 0)
		{
			v12 = mINPUT->mCameraRecordSpeed[0] * 0.1;
			mGXD->ChangeCameraForForward(v12);
			mINPUT->mPostCameraLength = mUTIL.ReturnLengthXYZ( &mGXD->mCameraEye.x, &mGXD->mCameraLook.x);
			if (mINPUT->mPostCameraLength < 10.0)
			{
				v11 = mINPUT->mCameraRecordSpeed[0] * -0.1;
				mGXD->ChangeCameraForForward(v11);
				mINPUT->mPostCameraLength = mUTIL.ReturnLengthXYZ( &mGXD->mCameraEye.x, &mGXD->mCameraLook.x);
			}
			goto LABEL_73;
		}
		if ((mGXD->mKeyboardImmediateData[31] & 0x80) != 0)
		{
			v10 = mINPUT->mCameraRecordSpeed[0] * -0.1;
			mGXD->ChangeCameraForForward(v10);
			mINPUT->mPostCameraLength = mUTIL.ReturnLengthXYZ( &mGXD->mCameraEye.x, &mGXD->mCameraLook.x);
		}
		else if ((mGXD->mKeyboardImmediateData[30] & 0x80) != 0)
		{
			v9 = mINPUT->mCameraRecordSpeed[1] * -1.0;
			mGXD->ChangeCameraForHorizon(v9);
		}
		else
		{
			if ((mGXD->mKeyboardImmediateData[32] & 0x80) == 0)
			{
				if ((mGXD->mKeyboardImmediateData[16] & 0x80) == 0)
				{
					if ((mGXD->mKeyboardImmediateData[18] & 0x80) == 0)
					{
						if ((mGXD->mKeyboardImmediateData[19] & 0x80) == 0)
						{
							if ((mGXD->mKeyboardImmediateData[33] & 0x80) != 0)
							{
								mGXD->mCameraEye.y = mGXD->mCameraEye.y - mINPUT->mCameraRecordSpeed[3];
								mGXD->SetCameraPosition(

									mGXD->mCameraEye.x,
									mGXD->mCameraEye.y,
									mGXD->mCameraEye.z,
									mGXD->mCameraLook.x,
									mGXD->mCameraLook.y,
									mGXD->mCameraLook.z);
								mTW2AddIn->SetCameraPosition(
									
									mGXD->mCameraEye.x,
									mGXD->mCameraEye.y,
									mGXD->mCameraEye.z,
									mGXD->mCameraLook.x,
									mGXD->mCameraLook.y,
									mGXD->mCameraLook.z);
								mINPUT->mPostCameraLength = mUTIL.ReturnLengthXYZ( &mGXD->mCameraEye.x, &mGXD->mCameraLook.x);
							}
							goto LABEL_73;
						}
					LABEL_49:
						mGXD->mCameraEye.y = mGXD->mCameraEye.y + mINPUT->mCameraRecordSpeed[3];
						mGXD->SetCameraPosition(

							mGXD->mCameraEye.x,
							mGXD->mCameraEye.y,
							mGXD->mCameraEye.z,
							mGXD->mCameraLook.x,
							mGXD->mCameraLook.y,
							mGXD->mCameraLook.z);
						mTW2AddIn->SetCameraPosition(
							
							mGXD->mCameraEye.x,
							mGXD->mCameraEye.y,
							mGXD->mCameraEye.z,
							mGXD->mCameraLook.x,
							mGXD->mCameraLook.y,
							mGXD->mCameraLook.z);
						mINPUT->mPostCameraLength = mUTIL.ReturnLengthXYZ( &mGXD->mCameraEye.x, &mGXD->mCameraLook.x);
						goto LABEL_73;
					}
					goto LABEL_47;
				}
				goto LABEL_45;
			}
			v8 = mINPUT->mCameraRecordSpeed[1] * 1.0;
			mGXD->ChangeCameraForHorizon(v8);
		}
	}
LABEL_73:
	for (i = 0; i < (int)mGXD->mKeyboardBufferedDataNum && (mGXD->mKeyboardBufferedData[i].dwData & 0x80) == 0; ++i)
		;
	if (i != mGXD->mKeyboardBufferedDataNum)
	{
		switch (mGXD->mKeyboardBufferedData[i].dwOfs)
		{
		case 2u:
			if (mMYINFO->mZoneAvatarInfo.aVisibleState || mINPUT->mCheckCameraRecord || mMYINFO->mPresentZoneNumber != 194)
			{
				if (mMYINFO->mZoneAvatarInfo.aVisibleState
					|| mINPUT->mCheckCameraRecord
					|| mMYINFO->mPresentZoneNumber != 270
					&& mMYINFO->mPresentZoneNumber != 271
					&& mMYINFO->mPresentZoneNumber != 272
					&& mMYINFO->mPresentZoneNumber != 273
					&& mMYINFO->mPresentZoneNumber != 274)
				{
					goto LABEL_240;
				}
				mGXD->SetCameraPosition(0.0, 230.0, 500.0, 0.0, 0.0, 0.0);
				mTW2AddIn->SetCameraPosition( 0.0, 230.0, 500.0, 0.0, 0.0, 0.0);
				mINPUT->mPostCameraLength = mUTIL.ReturnLengthXYZ( &mGXD->mCameraEye.x, &mGXD->mCameraLook.x);
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0] = mGXD->mCameraLook.x;
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[1] = mGXD->mCameraLook.y - 10.0;
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[2] = mGXD->mCameraLook.z;
				mPROCESSDATA->PROCESS_FOR_DATA_507(&mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0]);
			}
			else
			{
				mGXD->SetCameraPosition(0.0, 273.0, -892.0, 0.0, 63.0, -1342.0);
				mTW2AddIn->SetCameraPosition( 0.0, 273.0, -892.0, 0.0, 63.0, -1342.0);
				mINPUT->mPostCameraLength = mUTIL.ReturnLengthXYZ( &mGXD->mCameraEye.x, &mGXD->mCameraLook.x);
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0] = mGXD->mCameraLook.x;
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[1] = mGXD->mCameraLook.y - 10.0;
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[2] = mGXD->mCameraLook.z;
				mPROCESSDATA->PROCESS_FOR_DATA_507(&mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0]);
			}
			break;
		case 3u:
			if (mMYINFO->mZoneAvatarInfo.aVisibleState || mINPUT->mCheckCameraRecord || mMYINFO->mPresentZoneNumber != 194)
			{
				if (mMYINFO->mZoneAvatarInfo.aVisibleState
					|| mINPUT->mCheckCameraRecord
					|| mMYINFO->mPresentZoneNumber != 270
					&& mMYINFO->mPresentZoneNumber != 271
					&& mMYINFO->mPresentZoneNumber != 272
					&& mMYINFO->mPresentZoneNumber != 273
					&& mMYINFO->mPresentZoneNumber != 274)
				{
					goto LABEL_240;
				}
				mGXD->SetCameraPosition(0.0, 230.0, 3500.0, 0.0, 0.0, 4000.0);
				mTW2AddIn->SetCameraPosition( 0.0, 230.0, 3500.0, 0.0, 0.0, 4000.0);
				mINPUT->mPostCameraLength = mUTIL.ReturnLengthXYZ( &mGXD->mCameraEye.x, &mGXD->mCameraLook.x);
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0] = mGXD->mCameraLook.x;
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[1] = mGXD->mCameraLook.y - 10.0;
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[2] = mGXD->mCameraLook.z;
				mPROCESSDATA->PROCESS_FOR_DATA_507(&mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0]);
			}
			else
			{
				mGXD->SetCameraPosition(-892.0, 273.0, 0.0, -1342.0, 63.0, 0.0);
				mTW2AddIn->SetCameraPosition( -892.0, 273.0, 0.0, -1342.0, 63.0, 0.0);
				mINPUT->mPostCameraLength = mUTIL.ReturnLengthXYZ( &mGXD->mCameraEye.x, &mGXD->mCameraLook.x);
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0] = mGXD->mCameraLook.x;
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[1] = mGXD->mCameraLook.y - 10.0;
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[2] = mGXD->mCameraLook.z;
				mPROCESSDATA->PROCESS_FOR_DATA_507(&mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0]);
			}
			break;
		case 4u:
			if (mMYINFO->mZoneAvatarInfo.aVisibleState || mINPUT->mCheckCameraRecord || mMYINFO->mPresentZoneNumber != 194)
			{
				if (mMYINFO->mZoneAvatarInfo.aVisibleState
					|| mINPUT->mCheckCameraRecord
					|| mMYINFO->mPresentZoneNumber != 270
					&& mMYINFO->mPresentZoneNumber != 271
					&& mMYINFO->mPresentZoneNumber != 272
					&& mMYINFO->mPresentZoneNumber != 273
					&& mMYINFO->mPresentZoneNumber != 274)
				{
					goto LABEL_240;
				}
				mGXD->SetCameraPosition(0.0, 435.0, -1280.0, 0.0, 0.0, -800.0);
				mTW2AddIn->SetCameraPosition( 0.0, 435.0, -1280.0, 0.0, 0.0, -800.0);
				mINPUT->mPostCameraLength = mUTIL.ReturnLengthXYZ( &mGXD->mCameraEye.x, &mGXD->mCameraLook.x);
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0] = mGXD->mCameraLook.x;
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[1] = mGXD->mCameraLook.y - 10.0;
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[2] = mGXD->mCameraLook.z;
				mPROCESSDATA->PROCESS_FOR_DATA_507(&mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0]);
			}
			else
			{
				mGXD->SetCameraPosition(0.0, 273.0, 892.0, 0.0, 63.0, 1342.0);
				mTW2AddIn->SetCameraPosition( 0.0, 273.0, 892.0, 0.0, 63.0, 1342.0);
				mINPUT->mPostCameraLength = mUTIL.ReturnLengthXYZ( &mGXD->mCameraEye.x, &mGXD->mCameraLook.x);
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0] = mGXD->mCameraLook.x;
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[1] = mGXD->mCameraLook.y - 10.0;
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[2] = mGXD->mCameraLook.z;
				mPROCESSDATA->PROCESS_FOR_DATA_507(&mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0]);
			}
			break;
		case 5u:
			if (mMYINFO->mZoneAvatarInfo.aVisibleState || mINPUT->mCheckCameraRecord || mMYINFO->mPresentZoneNumber != 194)
			{
				if (mMYINFO->mZoneAvatarInfo.aVisibleState
					|| mINPUT->mCheckCameraRecord
					|| mMYINFO->mPresentZoneNumber != 270
					&& mMYINFO->mPresentZoneNumber != 271
					&& mMYINFO->mPresentZoneNumber != 272
					&& mMYINFO->mPresentZoneNumber != 273
					&& mMYINFO->mPresentZoneNumber != 274)
				{
					goto LABEL_240;
				}
				mGXD->SetCameraPosition(0.0, 435.0, 5250.0, 0.0, 0.0, 4800.0);
				mTW2AddIn->SetCameraPosition( 0.0, 435.0, 5250.0, 0.0, 0.0, 4800.0);
				mINPUT->mPostCameraLength = mUTIL.ReturnLengthXYZ( &mGXD->mCameraEye.x, &mGXD->mCameraLook.x);
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0] = mGXD->mCameraLook.x;
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[1] = mGXD->mCameraLook.y - 10.0;
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[2] = mGXD->mCameraLook.z;
				mPROCESSDATA->PROCESS_FOR_DATA_507(&mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0]);
			}
			else
			{
				mGXD->SetCameraPosition(892.0, 273.0, 0.0, 1342.0, 63.0, 0.0);
				mTW2AddIn->SetCameraPosition( 892.0, 273.0, 0.0, 1342.0, 63.0, 0.0);
				mINPUT->mPostCameraLength = mUTIL.ReturnLengthXYZ( &mGXD->mCameraEye.x, &mGXD->mCameraLook.x);
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0] = mGXD->mCameraLook.x;
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[1] = mGXD->mCameraLook.y - 10.0;
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[2] = mGXD->mCameraLook.z;
				mPROCESSDATA->PROCESS_FOR_DATA_507(&mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0]);
			}
			break;
		case 6u:
			if (mMYINFO->mZoneAvatarInfo.aVisibleState || mINPUT->mCheckCameraRecord || mMYINFO->mPresentZoneNumber != 194)
			{
				if (mMYINFO->mZoneAvatarInfo.aVisibleState
					|| mINPUT->mCheckCameraRecord
					|| mMYINFO->mPresentZoneNumber != 270
					&& mMYINFO->mPresentZoneNumber != 271
					&& mMYINFO->mPresentZoneNumber != 272
					&& mMYINFO->mPresentZoneNumber != 273
					&& mMYINFO->mPresentZoneNumber != 274)
				{
					goto LABEL_240;
				}
				mGXD->SetCameraPosition(890.0, 250.0, 1690.0, 520.0, -59.0, 1330.0);
				mTW2AddIn->SetCameraPosition( 890.0, 250.0, 1690.0, 520.0, -59.0, 1330.0);
				mINPUT->mPostCameraLength = mUTIL.ReturnLengthXYZ( &mGXD->mCameraEye.x, &mGXD->mCameraLook.x);
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0] = mGXD->mCameraLook.x;
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[1] = mGXD->mCameraLook.y - 10.0;
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[2] = mGXD->mCameraLook.z;
				mPROCESSDATA->PROCESS_FOR_DATA_507(&mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0]);
			}
			else
			{
				mGXD->SetCameraPosition(151.0, 366.0, -418.0, -419.0, 136.0, -531.0);
				mTW2AddIn->SetCameraPosition( 151.0, 366.0, -418.0, -419.0, 136.0, -531.0);
				mINPUT->mPostCameraLength = mUTIL.ReturnLengthXYZ( &mGXD->mCameraEye.x, &mGXD->mCameraLook.x);
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0] = mGXD->mCameraLook.x;
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[1] = mGXD->mCameraLook.y - 10.0;
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[2] = mGXD->mCameraLook.z;
				mPROCESSDATA->PROCESS_FOR_DATA_507(&mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0]);
			}
			break;
		case 7u:
			if (mMYINFO->mZoneAvatarInfo.aVisibleState || mINPUT->mCheckCameraRecord || mMYINFO->mPresentZoneNumber != 194)
			{
				if (mMYINFO->mZoneAvatarInfo.aVisibleState
					|| mINPUT->mCheckCameraRecord
					|| mMYINFO->mPresentZoneNumber != 270
					&& mMYINFO->mPresentZoneNumber != 271
					&& mMYINFO->mPresentZoneNumber != 272
					&& mMYINFO->mPresentZoneNumber != 273
					&& mMYINFO->mPresentZoneNumber != 274)
				{
					goto LABEL_240;
				}
				mGXD->SetCameraPosition(-890.0, 250.0, 710.0, -520.0, -59.0, 1050.0);
				mTW2AddIn->SetCameraPosition( -890.0, 250.0, 710.0, -520.0, -59.0, 1050.0);
				mINPUT->mPostCameraLength = mUTIL.ReturnLengthXYZ( &mGXD->mCameraEye.x, &mGXD->mCameraLook.x);
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0] = mGXD->mCameraLook.x;
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[1] = mGXD->mCameraLook.y - 10.0;
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[2] = mGXD->mCameraLook.z;
				mPROCESSDATA->PROCESS_FOR_DATA_507(&mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0]);
			}
			else
			{
				mGXD->SetCameraPosition(-418.0, 366.0, -151.0, -531.0, 136.0, 419.0);
				mTW2AddIn->SetCameraPosition( -418.0, 366.0, -151.0, -531.0, 136.0, 419.0);
				mINPUT->mPostCameraLength = mUTIL.ReturnLengthXYZ( &mGXD->mCameraEye.x, &mGXD->mCameraLook.x);
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0] = mGXD->mCameraLook.x;
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[1] = mGXD->mCameraLook.y - 10.0;
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[2] = mGXD->mCameraLook.z;
				mPROCESSDATA->PROCESS_FOR_DATA_507(&mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0]);
			}
			break;
		case 8u:
			if (mMYINFO->mZoneAvatarInfo.aVisibleState || mINPUT->mCheckCameraRecord || mMYINFO->mPresentZoneNumber != 194)
			{
				if (mMYINFO->mZoneAvatarInfo.aVisibleState
					|| mINPUT->mCheckCameraRecord
					|| mMYINFO->mPresentZoneNumber != 270
					&& mMYINFO->mPresentZoneNumber != 271
					&& mMYINFO->mPresentZoneNumber != 272
					&& mMYINFO->mPresentZoneNumber != 273
					&& mMYINFO->mPresentZoneNumber != 274)
				{
					goto LABEL_240;
				}
				mGXD->SetCameraPosition(-890.0, 250.0, 2310.0, -535.0, -59.0, 2670.0);
				mTW2AddIn->SetCameraPosition( -890.0, 250.0, 2310.0, -535.0, -59.0, 2670.0);
				mINPUT->mPostCameraLength = mUTIL.ReturnLengthXYZ( &mGXD->mCameraEye.x, &mGXD->mCameraLook.x);
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0] = mGXD->mCameraLook.x;
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[1] = mGXD->mCameraLook.y - 10.0;
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[2] = mGXD->mCameraLook.z;
				mPROCESSDATA->PROCESS_FOR_DATA_507(&mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0]);
			}
			else
			{
				mGXD->SetCameraPosition(-151.0, 366.0, 418.0, 419.0, 136.0, 531.0);
				mTW2AddIn->SetCameraPosition( -151.0, 366.0, 418.0, 419.0, 136.0, 531.0);
				mINPUT->mPostCameraLength = mUTIL.ReturnLengthXYZ( &mGXD->mCameraEye.x, &mGXD->mCameraLook.x);
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0] = mGXD->mCameraLook.x;
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[1] = mGXD->mCameraLook.y - 10.0;
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[2] = mGXD->mCameraLook.z;
				mPROCESSDATA->PROCESS_FOR_DATA_507(&mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0]);
			}
			break;
		case 9u:
			if (mMYINFO->mZoneAvatarInfo.aVisibleState || mINPUT->mCheckCameraRecord || mMYINFO->mPresentZoneNumber != 194)
			{
				if (mMYINFO->mZoneAvatarInfo.aVisibleState
					|| mINPUT->mCheckCameraRecord
					|| mMYINFO->mPresentZoneNumber != 270
					&& mMYINFO->mPresentZoneNumber != 271
					&& mMYINFO->mPresentZoneNumber != 272
					&& mMYINFO->mPresentZoneNumber != 273
					&& mMYINFO->mPresentZoneNumber != 274)
				{
					goto LABEL_240;
				}
				mGXD->SetCameraPosition(890.0, 250.0, 3290.0, 530.0, -59.0, 2925.0);
				mTW2AddIn->SetCameraPosition( 890.0, 250.0, 3290.0, 530.0, -59.0, 2925.0);
				mINPUT->mPostCameraLength = mUTIL.ReturnLengthXYZ( &mGXD->mCameraEye.x, &mGXD->mCameraLook.x);
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0] = mGXD->mCameraLook.x;
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[1] = mGXD->mCameraLook.y - 10.0;
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[2] = mGXD->mCameraLook.z;
				mPROCESSDATA->PROCESS_FOR_DATA_507(&mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0]);
			}
			else
			{
				mGXD->SetCameraPosition(418.0, 366.0, 151.0, 531.0, 136.0, -419.0);
				mTW2AddIn->SetCameraPosition( 418.0, 366.0, 151.0, 531.0, 136.0, -419.0);
				mINPUT->mPostCameraLength = mUTIL.ReturnLengthXYZ( &mGXD->mCameraEye.x, &mGXD->mCameraLook.x);
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0] = mGXD->mCameraLook.x;
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[1] = mGXD->mCameraLook.y - 10.0;
				mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[2] = mGXD->mCameraLook.z;
				mPROCESSDATA->PROCESS_FOR_DATA_507(&mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0]);
			}
			break;
		case 0xAu:
			if (mMYINFO->mZoneAvatarInfo.aVisibleState || mINPUT->mCheckCameraRecord || mMYINFO->mPresentZoneNumber != 194)
				goto LABEL_240;
			mGXD->SetCameraPosition(1185.0, 1453.0, 1185.0, 0.0, 0.0, 63.0);
			mTW2AddIn->SetCameraPosition( 1185.0, 1453.0, 1185.0, 0.0, 0.0, 63.0);
			mINPUT->mPostCameraLength = mUTIL.ReturnLengthXYZ( &mGXD->mCameraEye.x, &mGXD->mCameraLook.x);
			mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0] = mGXD->mCameraLook.x;
			mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[1] = mGXD->mCameraLook.y - 10.0;
			mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[2] = mGXD->mCameraLook.z;
			mPROCESSDATA->PROCESS_FOR_DATA_507(&mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aLocation[0]);
			break;
		case 0x19u:
			if (mMYINFO->mZoneAvatarInfo.aVisibleState || !mINPUT->mCheckCameraRecord)
				goto LABEL_240;
			v2 = mINPUT->mCameraRecordState;
			if (v2 == 1)
			{
				mINPUT->mCameraRecordState = 2;
			}
			else if (v2 == 2)
			{
				mINPUT->mCameraRecordState = 1;
			}
			break;
		case 0x26u:
			if (mMYINFO->mZoneAvatarInfo.aVisibleState || !mINPUT->mCheckCameraRecord)
				goto LABEL_240;
			v1 = mINPUT->mCameraRecordState;
			if (v1 == 1)
			{
				if (strcmp(mINPUT->mCameraRecordPostAvatarName, ""))
					mINPUT->mCameraRecordState = 3;
			}
			else if (v1 == 3)
			{
				mINPUT->mCameraRecordState = 1;
				strcpy(mINPUT->mCameraRecordPostAvatarName, "");
			}
			break;
		case 0x2Cu:
			if (mMYINFO->mZoneAvatarInfo.aVisibleState || !mINPUT->mCheckCameraRecord)
				goto LABEL_240;
			mINPUT->mCameraRecordSpeed[mINPUT->mCameraRecordChangeSpeedIndex] = mINPUT->mCameraRecordSpeed[mINPUT->mCameraRecordChangeSpeedIndex]
				- 1.0;
			if (mINPUT->mCameraRecordSpeed[mINPUT->mCameraRecordChangeSpeedIndex] < 1.0)
				mINPUT->mCameraRecordSpeed[mINPUT->mCameraRecordChangeSpeedIndex] = 1.0;
			break;
		case 0x2Du:
			if (mMYINFO->mZoneAvatarInfo.aVisibleState || !mINPUT->mCheckCameraRecord)
				goto LABEL_240;
			if (++mINPUT->mCameraRecordChangeSpeedIndex == 4)
				mINPUT->mCameraRecordChangeSpeedIndex = 0;
			break;
		case 0x2Eu:
			if (mMYINFO->mZoneAvatarInfo.aVisibleState || !mINPUT->mCheckCameraRecord)
				goto LABEL_240;
			mINPUT->mCameraRecordSpeed[mINPUT->mCameraRecordChangeSpeedIndex] = mINPUT->mCameraRecordSpeed[mINPUT->mCameraRecordChangeSpeedIndex]
				+ 1.0;
			if (mINPUT->mCameraRecordSpeed[mINPUT->mCameraRecordChangeSpeedIndex] > 100.0)
				mINPUT->mCameraRecordSpeed[mINPUT->mCameraRecordChangeSpeedIndex] = 100.0;
			break;
		case 0x58u:
			mUTIL.ProcessForScreenShot();
			break;
		case 0xC7u:
			if (mMYINFO->mZoneAvatarInfo.aVisibleState)
				goto LABEL_240;
			mINPUT->mCheckDisplayUI = !mINPUT->mCheckDisplayUI;
			break;
		case 0xC9u:
			if (mMYINFO->mZoneAvatarInfo.aVisibleState)
				goto LABEL_240;
			if (++mINPUT->mDisplayInfoState == 4)
				mINPUT->mDisplayInfoState = 1;
			break;
		case 0xCFu:
			if (mMYINFO->mZoneAvatarInfo.aVisibleState)
				goto LABEL_240;
			if (mINPUT->mCheckCameraRecord)
			{
				mINPUT->InitForCameraRecord();
				mINPUT->mCheckCameraRecord = 0;
				mINPUT->mCameraRecordState = 0;
			}
			else
			{
				mINPUT->InitForCameraRecord();
				mINPUT->mCheckCameraRecord = 1;
				mINPUT->mCameraRecordState = 1;
			}
			break;
		default:
		LABEL_240:
			if (mMYINFO->mZoneAvatarInfo.aVisibleState
				|| !mINPUT->mCheckCameraRecord
				|| (mGXD->mKeyboardImmediateData[17] & 0x80) == 0
				&& (mGXD->mKeyboardImmediateData[31] & 0x80) == 0
				&& (mGXD->mKeyboardImmediateData[30] & 0x80) == 0
				&& (mGXD->mKeyboardImmediateData[32] & 0x80) == 0
				&& (mGXD->mKeyboardImmediateData[19] & 0x80) == 0
				&& (mGXD->mKeyboardImmediateData[33] & 0x80) == 0
				&& (mGXD->mKeyboardImmediateData[16] & 0x80) == 0
				&& (mGXD->mKeyboardImmediateData[18] & 0x80) == 0)
			{
				if (!mEDITBOX->mDataIndex)
					goto LABEL_262;
				if (mEDITBOX->mDataIndex == 6)
				{
					for (i = 0; i < (int)mGXD->mKeyboardBufferedDataNum && (mGXD->mKeyboardBufferedData[i].dwData & 0x80) == 0; ++i)
						;
					if (i != mGXD->mKeyboardBufferedDataNum && mGXD->mKeyboardBufferedData[i].dwOfs == 1)
					{
					LABEL_262:
						if ((!mHELPUI->mActive || !mHELPUI->unk[0])
							&& mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aSort != 11
							&& mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aSort != 12
							&& mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aSort != 33
							&& mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aSort != 34
							&& mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aSort != 35
							&& mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aSort != 36
							&& mPLAY->mAVATAR_OBJECT[0].mDATA.aAction.aSort != 37
							&& !mUI->KEYBOARD())
						{
							mMAIN->KEYBOARD();
						}
					}
				}
			}
			break;
		}
	}
}
