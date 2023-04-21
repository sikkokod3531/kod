void W_USE_INVENTORY_ITEM_SEND(int tUserIndex)
{
	__LogMgr()->Log("![RUN]  %s.\n", __FUNCTION__);
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tPage;
	int tIndex;
	int tValue;


	CopyMemory(&tPage, &tPacket[1], 4);
	CopyMemory(&tIndex, &tPacket[5], 4);
	CopyMemory(&tValue, &tPacket[9], 4);
	// 2009.11.23 : ±è¼º¼ö :µð¹ö±ëÀ» À§ÇÑ ³Ö¾î¶² ÄÚµå	
	// __LogMgr()->Log("![INFO] tPage = %d  , tIndex = %d , tValue = %d \n",tPage ,tIndex ,tValue  );

	if ((tPage < 0) || (tPage > 1) || (tIndex < 0) || (tIndex > (MAX_INVENTORY_SLOT_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int index01;
	int index02;
	ITEM_INFO* tITEM_INFO;
	ITEM_INFO* tITEM_INFO1;
	SKILL_INFO* tSKILL_INFO;
	int tEquipIndex;
	int tEquip[4];
	int tEquipSocket[3];
	int tItemLLevel;
	int tItemHLevel;
	int tTribeItemList[9];
	int tRandomValue;
	int tItemType;
	int tItemSort;
	int tSearchNum;
	int tMoney;
	int CpTowerNum;
	int CpTowerMapNum;
	int CpToverVlue;
	const int tItemListNum = 5;
	int iPage = 0;
	int iInvenSlot = 0;
	int iInvenPage = 0;
	int iInvenIndex = 0;
	int tItemCount = 0;
	int tPageList[tItemListNum];
	int tInvenSlotList[tItemListNum];
	int tInvenIndexList[tItemListNum];
	int tItemList[tItemListNum][2];
	//int tItemCountList[tItemListNum];
	int tItemValueList[tItemListNum];
	int tItemRecognitionList[tItemListNum];
	int temp_AddTime = 0;
	int tDumyPageList[tItemListNum];
	int tDumyInvenSlotList[tItemListNum];
	int tBroadcastInfoSort;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];
	time_t tCountSeconds;
	struct tm* tPresentTime;
	char cDate[100];
	unsigned int iDate = 0;
	unsigned int tZone84Date = 0;
	int tProtectIS = 0;
	int tItemNumber = 0; // »ç¿ëÇÒ ¾ÆÀÌÅÛ ¹øÈ£ ÀúÀå¿ë º¯¼ö.
	int tAddExp;

	int iInvenPage1[8];
	int iInvenIndex1[8];
	int iInvenSlot1[8];
	int SetBonus = 0;

	int title = 0;
	int CpValue[14];
	int AddCp = 0;
	CpValue[0] = 800;
	CpValue[1] = 1700;
	CpValue[2] = 2500;
	CpValue[3] = 3400;
	CpValue[4] = 4200;
	CpValue[5] = 5100;
	CpValue[6] = 5900;
	CpValue[7] = 6800;
	CpValue[8] = 7600;
	CpValue[9] = 8500;
	CpValue[10] = 9300;
	CpValue[11] = 10000;
	CpValue[12] = 10000;
	CpValue[13] = 10000;
	int AnimalIndex;
	ZeroMemory(tBroadcastInfoData, sizeof(tBroadcastInfoData));

	if (tPage == 1)
	{
		if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	tITEM_INFO = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0]);
	if (tITEM_INFO == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	tItemNumber = tITEM_INFO->iIndex;
	switch (tITEM_INFO->iSort)
	{
	case  5: //[¹«°øºñ±Þ]
		if (tITEM_INFO->iEquipInfo[0] != 1)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe != (tITEM_INFO->iEquipInfo[0] - 2))
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}

		if ((mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2) < (tITEM_INFO->iLevelLimit + tITEM_INFO->iMartialLevelLimit))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < MAX_SKILL_SLOT_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] == tITEM_INFO->iGainSkillNumber)
			{
				break;
			}
		}
		if (index01 < MAX_SKILL_SLOT_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tSKILL_INFO = mSKILL.Search(tITEM_INFO->iGainSkillNumber);
		if (tSKILL_INFO == NULL)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aSkillPoint < tSKILL_INFO->sLearnSkillPoint)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch (tSKILL_INFO->sType)
		{
		case 1:
			for (index01 = 0; index01 < 10; index01++)
			{
				if (mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] < 1)
				{
					break;
				}
			}
			if (index01 == 10)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 2:
			for (index01 = 20; index01 < 30; index01++)
			{
				if (mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] < 1)
				{
					break;
				}
			}
			if (index01 == 30)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 3:
			for (index01 = 10; index01 < 20; index01++)
			{
				if (mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] < 1)
				{
					break;
				}
			}
			if (index01 == 20)
			{
				for (index01 = 30; index01 < 40; index01++)
				{
					if (mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] < 1)
					{
						break;
					}
				}
				if (index01 == 40)
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
			}
			break;
		case 4:
			for (index01 = 10; index01 < 20; index01++)
			{
				if (mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] < 1)
				{
					break;
				}
			}
			if (index01 == 20)
			{
				for (index01 = 30; index01 < 40; index01++)
				{
					if (mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] < 1)
					{
						break;
					}
				}
				if (index01 == 40)
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
			}
			break;
		default:
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aSkillPoint -= tSKILL_INFO->sLearnSkillPoint;
		mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] = tSKILL_INFO->sIndex;
		mUSER[tUserIndex].mAvatarInfo.aSkill[index01][1] = tSKILL_INFO->sLearnSkillPoint;
		//mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage][tIndex][2] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case  6: //[Àå½Ä]
	case  7: //[¸ñ°ÉÀÌ]
	case  8: //[¸ÁÅä]
	case  9: //[º¹Àå]
	case 10: //[Àå°©]
	case 11: //[¹ÝÁö]
	case 12: //[½Å¹ß]
	case 13: //[°Ë]
	case 14: //[µµ]
	case 15: //[Åõ¿Á]
	case 16: //[ÅÂµµ]
	case 17: //[½Ö±Ø]
	case 18: //[ºñÆÄ]
	case 19: //[¹Úµµ]
	case 20: //[ÀåÃ¢]
	case 21: //[±Ý°­Àú]
	case 22: //[¿µ¹°]
	case 28:
	case 29:
	case 30:
	case 31:
	case 32:
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort != 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (!mUTIL.CheckPossibleEquipItem(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aPreviousTribe, -1, (mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2)))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tEquipIndex = tITEM_INFO->iEquipInfo[1] - 2;
		if ((tEquipIndex < 0) || (tEquipIndex > (MAX_EQUIP_SLOT_NUM - 1)))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tEquip[0] = mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][0];
		tEquip[1] = mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][1];
		tEquip[2] = mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][2];
		tEquip[3] = mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][3];
		tEquipSocket[0] = mUSER[tUserIndex].mAvatarInfo.EquipSocket[tEquipIndex][0];
		tEquipSocket[1] = mUSER[tUserIndex].mAvatarInfo.EquipSocket[tEquipIndex][1];
		tEquipSocket[2] = mUSER[tUserIndex].mAvatarInfo.EquipSocket[tEquipIndex][2];
		mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][0] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0];
		mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3];
		mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4];
		mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][3] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5];
		mUSER[tUserIndex].mAvatarInfo.EquipSocket[tEquipIndex][0] = mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage][tIndex][0];
		mUSER[tUserIndex].mAvatarInfo.EquipSocket[tEquipIndex][1] = mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage][tIndex][1];
		mUSER[tUserIndex].mAvatarInfo.EquipSocket[tEquipIndex][2] = mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage][tIndex][2];
		mAVATAR_OBJECT[tUserIndex].mDATA.aEquipForView[tEquipIndex][0] = mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][0];
		mAVATAR_OBJECT[tUserIndex].mDATA.aEquipForView[tEquipIndex][1] = mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][2];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tEquip[0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = tEquip[1];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = tEquip[2];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = tEquip[3];
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage][tIndex][0] = tEquipSocket[0];
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage][tIndex][1] = tEquipSocket[1];
		mUSER[tUserIndex].mAvatarInfo.InventorySocket[tPage][tIndex][2] = tEquipSocket[2];
		mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aType = (unsigned char)mAVATAR_OBJECT[tUserIndex].GetWeaponClass() * 2;
		mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aFrame = 0.0f;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue > mAVATAR_OBJECT[tUserIndex].GetMaxLife())
		{
			mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife();
		}
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue > mAVATAR_OBJECT[tUserIndex].GetMaxMana())
		{
			mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana();
		}
		if (tEquipIndex == 7)
		{
			mAVATAR_OBJECT[tUserIndex].ProcessForDeleteEffectValue();
		}

		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 23:
	case 24:
		return;
	case 25:
		return;
	case 26:
		for (index01 = 0; index01 < 10; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.Bottle[index01] == tITEM_INFO->iIndex)
			{
				break;
			}
		}
		if (index01 < 10)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < 10; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.Bottle[index01] == 0)
			{
				break;
			}
		}
		if (index01 == 10)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		//mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.Bottle[index01] = tITEM_INFO->iIndex;
		mUSER[tUserIndex].mAvatarInfo.BottlePrice[index01] = 30;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, index01);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}

	// 2009.11.23 : ±è¼º¼ö :µð¹ö±ëÀ» À§ÇÑ ³Ö¾î¶² ÄÚµå
	switch (tITEM_INFO->iIndex)
	{
	case 301:
	case 302:
	case 303:
	case 304:
	case 305:
	case 306:
	case 307:
	case 308:
	case 309:
	case 310:
	case 311:
	case 312:
	case 313:
	case 314:
	case 315:
	case 316:
	case 317:
	case 318:
	case 319:
	case 320:
	case 321:
	case 322:
	case 323:
	case 324:
	case 325:
	case 326:
	case 327:
	case 328:
	case 329:
	case 330:
	case 331:
	case 332:
	case 333:
	case 334:
	case 335:
	case 336:
	case 337:
	case 338:
	case 339:
	case 340:
	case 341:
	case 342:
	case 343:
	case 344:
	case 345:
	case 346:
	case 347:
	case 348:
	case 349:
	case 350:
	case 351:
	case 352:
	case 353:
	case 354:
	case 355:
	case 356:
	case 357:
	case 358:
	case 359:
	case 360:
	case 361:
	case 362:
	case 363:
	case 364:
	case 365:
	case 366:
	case 367:
	case 368:
	case 369:
	case 370:
	case 371:
	case 372:
	case 373:
	case 374:
	case 375:
	case 376:
	case 377:
	case 378:
	case 379:
	case 380:
	case 381:
	case 382:
	case 383:
	case 384:
	case 385:
	case 386:
	case 387:
	case 394:
	case 395:
	case 396:
	case 397:
	case 398:
	case 399:
	case 400:
	case 401:
	case 402:
	case 403:
	case 404:
	case 405:
	case 406:
	case 407:
	case 408:
	case 409:
	case 410:
	case 411:
	case 412:
	case 413:
	case 414:
	case 415:
	case 416:
	case 417:
	case 418:
	case 419:
	case 420:
	case 421:
	case 422:
	case 423:
	case 424:
	case 425:
	case 426:
	case 427:
	case 428:
	case 429:
	case 430:
	case 431:
	case 432:
	case 433:
	case 434:
	case 435:
	case 436:
	case 437:
	case 438:
	case 439:
	case 440:
	case 441:
	case 442:
	case 443:
	case 444:
	case 445:
	case 446:
	case 447:
	case 448:
	case 449:
	case 450:
	case 451:
	case 452:
	case 453:
	case 454:
	case 455:
	case 456:
	case 1891:
	case 1892:
	case 1893:
	case 2146:
	case 2147:
	case 2148:
	case 7003:
	case 7004:
	case 7005:
	case 7006:
	case 7007:
	case 18028:
	case 18029:
	case 18030:
	case 18031:
	case 18032:
	case 18033:
	case 18034:
	case 18035:
	case 18036:
	case 18037:
	case 18038:
	case 18039:
	case 18040:
	case 18041:
	case 18042:
	case 17140:
	case 17141:
	case 17142:
	case 17143:
	case 17144:
	case 17145:
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.Costume[index01] == tITEM_INFO->iIndex)
			{
				break;
			}
		}
		if (index01 < MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.Costume[index01] == 0)
			{
				break;
			}
		}
		if (index01 == MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tValue = index01;
		mUSER[tUserIndex].mAvatarInfo.Costume[tValue] = tITEM_INFO->iIndex;
		tITEM_INFO1 = mITEM.Search(tValue);
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, 0, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 1301:
	case 1302:
	case 1303:
	case 1304:
	case 1305:
	case 1306:
	case 1307:
	case 1308:
	case 1309:
	case 1313:
	case 1314:
	case 1315:
	case 1316:
	case 1317:
	case 1318:
	case 1319:
	case 1320:
	case 1321:
	case 1322:
	case 1323:
	case 1324:
	case 1325:
	case 1326:
	case 1327:
	case 1328:
	case 1329:
	case 1330:
	case 1331:
		//Karahan binekleri
	case 250:
	case 251:
	case 252:
	case 253:
	case 254:
	case 255:
	case 256:
	case 257:
	case 258:
	case 259:
	case 260:
	case 261:
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == tITEM_INFO->iIndex)
			{
				break;
			}
		}
		if (index01 < MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == 0)
			{
				break;
			}
		}
		if (index01 == MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tValue = index01;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, 0, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aAnimal[tValue] = tITEM_INFO->iIndex;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		if (mUSER[tUserIndex].mExtraAvatarInfo.AnimalTransferInventory[tPage][tIndex] > 0)
		{
			mUSER[tUserIndex].mAvatarInfo.AnimalStat[tValue] = mUSER[tUserIndex].mExtraAvatarInfo.AnimalTransferInventory[tPage][tIndex];
		}
		mUSER[tUserIndex].mExtraAvatarInfo.AnimalTransferInventory[tPage][tIndex] = 0;
		mUSER[tUserIndex].mAvatarInfo.AnimalExp[tValue] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 1017:
	case 506:
		if (mUSER[tUserIndex].mAvatarInfo.aEatLifePotion >= 200)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aEatLifePotion += 1;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aEatLifePotion, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 1018:
	case 507:
		if (mUSER[tUserIndex].mAvatarInfo.aEatManaPotion >= 200)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aEatManaPotion += 1;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aEatManaPotion, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 1093:
	case 508:
		if (mUSER[tUserIndex].mAvatarInfo.AgiElx >= 200)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.AgiElx += 1;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.AgiElx, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 1082:
	case 509:
		if (mUSER[tUserIndex].mAvatarInfo.StrElx >= 200)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.StrElx += 1;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.StrElx, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 512://Etkinlik Kutusu
		tRandomValue = rand() % 200;
		if (tRandomValue < 65) {
			tValue = 691;// 5 Cp
		}
		else if (tRandomValue < 125) {
			tValue = 1023;// 15 eritme
		}
		else if (tRandomValue < 165) {
			tValue = 1072;// 100m bar
		}
		else if (tRandomValue < 170) {
			tValue = 602;// Pet Box
		}
		else if (tRandomValue < 175) {
			tValue = 2249;// Cape Box
		}
		else if (tRandomValue < 180) {
			tValue = 1422;// Eritme Tılsımı
		}
		else if (tRandomValue < 190) {
			tValue = 1316;// Bambi
		}
		else {
			tValue = 601;
		}
		tITEM_INFO1 = mITEM.Search(tValue);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		if (tITEM_INFO1->iSort == 99)
		{
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 1;
		}
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4],
			tITEM_INFO1->iIndex, tITEM_INFO1->iName, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 553:
		mUSER[tUserIndex].mAvatarInfo.FishingTime += 180;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.FishingTime, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 577:
		mUSER[tUserIndex].mAvatarInfo.Sarmasik += 30;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.PreServeCharm, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 578:
		if ((mUSER[tUserIndex].mAvatarInfo.YeniElx / 1000) >= 200)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.YeniElx += 1000;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, (mUSER[tUserIndex].mAvatarInfo.YeniElx / 1000), 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 579:
		if ((mUSER[tUserIndex].mAvatarInfo.YeniElx % 1000) >= 200)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.YeniElx += 1;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.YeniElx % 1000, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 580://Kırmızı Balık
		tRandomValue = myrand(0, 10000);

		if (tRandomValue < 9)
		{
			switch (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe)
			{
			case 0:
				tValue = 216;
				break;
			case 1:
				tValue = 217;
				break;
			case 2:
				tValue = 218;
				break;
			}
		}
		else if (tRandomValue < 109)
		{
			tValue = 699;//döküm 1-3
		}
		else if (tRandomValue < 1000)
		{
			tValue = 1072;
		}
		else if (tRandomValue < 2000)
		{
			tValue = 1023;
		}
		else if (tRandomValue < 3000)
		{
			tValue = 2249;
		}
		else if (tRandomValue < 4500)
		{
			tValue = 602;
		}
		else if (tRandomValue < 6000)
		{
			tValue = 1449;
		}
		else if (tRandomValue < 6500)
		{
			tValue = 17087;
		}
		else if (tRandomValue < 7000)
		{
			tValue = 17088;
		}
		else if (tRandomValue < 7500)
		{
			tValue = 17091;
		}
		else if (tRandomValue < 8000)
		{
			tValue = 17092;
		}
		else if (tRandomValue < 8500)
		{
			tValue = 1376;
		}
		else if (tRandomValue < 9000)
		{
			tValue = 1374;
		}
		else if (tRandomValue < 9100)
		{
			tValue = 2169;
		}
		else if (tRandomValue < 9200)
		{
			tValue = 1243;
		}
		else if (tRandomValue < 9300)
		{
			tValue = 1378;
		}
		else if (tRandomValue < 9800)
		{
			tValue = 1375;
		}
		else if (tRandomValue < 9900)
		{
			tValue = 901;
		}
		else
		{
			tValue = 17104;
		}

		tITEM_INFO1 = mITEM.Search(tValue);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		if (tITEM_INFO1->iSort == 99)
		{
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 1;
		}
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4],
			tITEM_INFO1->iIndex, tITEM_INFO1->iName, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 581://Sarı Balık
		tRandomValue = rand() % 10000;

		if (tRandomValue < 20)
		{
			tValue = 577;
		}
		else if (tRandomValue < 1000)
		{
			tValue = 1023;
		}
		else if (tRandomValue < 2000)
		{
			tValue = 506;
		}
		else if (tRandomValue < 3000)
		{
			tValue = 507;
		}
		else if (tRandomValue < 4000)
		{
			tValue = 508;
		}
		else if (tRandomValue < 5000)
		{
			tValue = 509;
		}
		else if (tRandomValue < 6000)
		{
			tValue = 578;
		}
		else if (tRandomValue < 7000)
		{
			tValue = 579;
		}
		else if (tRandomValue < 7500)
		{
			tValue = 1072;
		}
		else if (tRandomValue < 8000)
		{
			tValue = 1374;
		}
		else if (tRandomValue < 8500)
		{
			tValue = 1422;
		}
		else if (tRandomValue < 9000)
		{
			tValue = 2249;
		}
		else if (tRandomValue < 9500)
		{
			tValue = 602;
		}
		else
		{
			tValue = 1372;
		}

		tITEM_INFO1 = mITEM.Search(tValue);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		if (tITEM_INFO1->iSort == 99)
		{
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 1;
		}
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4],
			tITEM_INFO1->iIndex, tITEM_INFO1->iName, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case  601://%10 Binek Kutusu
		tRandomValue = rand() % 100;
		if (tRandomValue < 6)
		{
			tValue = 1304;
		}
		else if (tRandomValue < 12)
		{
			tValue = 1314;
		}
		else if (tRandomValue < 20)
		{
			tValue = 1318;
		}
		else if (tRandomValue < 35)
		{
			tValue = 1321;
		}
		else if (tRandomValue < 50)
		{
			tValue = 1305;
		}
		else if (tRandomValue < 70)
		{
			tValue = 1306;
		}
		else if (tRandomValue < 90)
		{
			tValue = 1324;
		}
		else
		{
			tValue = 1327;
		}
		tITEM_INFO1 = mITEM.Search(tValue);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4],
			tITEM_INFO1->iIndex, tITEM_INFO1->iName, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 602://Pet Box
		tRandomValue = rand() % 500;
		if (tRandomValue < 75)
		{
			tValue = 1002;
		}
		else if (tRandomValue < 150)
		{
			tValue = 1003;
		}
		else if (tRandomValue < 225)
		{
			tValue = 1004;
		}
		else if (tRandomValue < 300)
		{
			tValue = 1005;
		}
		else if (tRandomValue < 320)
		{
			tValue = 1006;
		}
		else if (tRandomValue < 340)
		{
			tValue = 1007;
		}
		else if (tRandomValue < 360)
		{
			tValue = 1008;
		}
		else if (tRandomValue < 380)
		{
			tValue = 1009;
		}
		else if (tRandomValue < 400)
		{
			tValue = 1010;
		}
		else if (tRandomValue < 420)
		{
			tValue = 1011;
		}
		else if (tRandomValue < 428)
		{
			tValue = 1012;
		}
		else if (tRandomValue < 443)
		{
			tValue = 1013;
		}
		else if (tRandomValue < 458)
		{
			tValue = 1014;
		}
		else if (tRandomValue < 473)
		{
			tValue = 1015;
		}
		else if (tRandomValue < 475)
		{
			tValue = 1016;
		}
		else if (tRandomValue < 495)
		{
			tValue = 1072;
		}
		else
		{
			tValue = 1235;
		}

		tRandomValue = myrand(0, 1000);
		if (tRandomValue < 1)
		{
			tValue = 2169;
		}

		tITEM_INFO1 = mITEM.Search(tValue);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4],
			tITEM_INFO1->iIndex, tITEM_INFO1->iName, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 612: // %5 Binek Hapı
		if (mUSER[tUserIndex].mAvatarInfo.aAnimalIndex < 10)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if ((mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] % 1000000) == 100000)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(2, tPage, tIndex, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] += 1000;
		if ((mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] % 1000000) > 100000)
		{
			mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] -= ((mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] % 1000000) - 100000);
		}
		tValue = mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10];
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, (mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] % 1000000), 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 613:
		mUSER[tUserIndex].mAvatarInfo.MountAbsorb += 60;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.MountAbsorb, 0, 0, 0, 0, 0);
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(78, mUSER[tUserIndex].mAvatarInfo.MountAbsorb);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case  635://%15 Binek Kutusu
		tRandomValue = rand() % 100;

		if (tRandomValue < 2)
		{
			tValue = 1329;
		}
		else if (tRandomValue < 6)
		{
			tValue = 1307;
		}
		else if (tRandomValue < 12)
		{
			tValue = 1315;
		}
		else if (tRandomValue < 20)
		{
			tValue = 1319;
		}
		else if (tRandomValue < 35)
		{
			tValue = 1322;
		}
		else if (tRandomValue < 50)
		{
			tValue = 1308;
		}
		else if (tRandomValue < 70)
		{
			tValue = 1309;
		}
		else if (tRandomValue < 90)
		{
			tValue = 1325;
		}
		else
		{
			tValue = 1328;
		}
		tITEM_INFO1 = mITEM.Search(tValue);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4],
			tITEM_INFO1->iIndex, tITEM_INFO1->iName, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 636: //[È°·Â´Ü]
		if (mUSER[tUserIndex].mAvatarInfo.aEatLifePotion >= 200)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aEatLifePotion += 10;
		if (mUSER[tUserIndex].mAvatarInfo.aEatLifePotion > 200)
		{
			mUSER[tUserIndex].mAvatarInfo.aEatLifePotion = 200;
		}
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aEatLifePotion, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 637: //[È°·Â´Ü]
		if (mUSER[tUserIndex].mAvatarInfo.aEatManaPotion >= 200)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aEatManaPotion += 10;
		if (mUSER[tUserIndex].mAvatarInfo.aEatManaPotion > 200)
		{
			mUSER[tUserIndex].mAvatarInfo.aEatManaPotion = 200;
		}
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aEatManaPotion, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 638: //[È°·Â´Ü]
		if (mUSER[tUserIndex].mAvatarInfo.StrElx >= 200)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.StrElx += 10;
		if (mUSER[tUserIndex].mAvatarInfo.StrElx > 200)
		{
			mUSER[tUserIndex].mAvatarInfo.StrElx = 200;
		}
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.StrElx, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 639: //[È°·Â´Ü]
		if (mUSER[tUserIndex].mAvatarInfo.AgiElx >= 200)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.AgiElx += 10;
		if (mUSER[tUserIndex].mAvatarInfo.AgiElx > 200)
		{
			mUSER[tUserIndex].mAvatarInfo.AgiElx = 200;
		}
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.AgiElx, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 640: //[È°·Â´Ü]
		if ((mUSER[tUserIndex].mAvatarInfo.YeniElx / 1000) >= 200)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.YeniElx += 10000;
		if ((mUSER[tUserIndex].mAvatarInfo.YeniElx / 1000) > 200)
		{
			mUSER[tUserIndex].mAvatarInfo.YeniElx -= ((mUSER[tUserIndex].mAvatarInfo.YeniElx / 1000) - 200) * 1000;
		}
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, (mUSER[tUserIndex].mAvatarInfo.YeniElx / 1000), 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 641: //[È°·Â´Ü]
		if ((mUSER[tUserIndex].mAvatarInfo.YeniElx % 1000) >= 200)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.YeniElx += 10;
		if ((mUSER[tUserIndex].mAvatarInfo.YeniElx % 1000) > 200)
		{
			mUSER[tUserIndex].mAvatarInfo.YeniElx = ((mUSER[tUserIndex].mAvatarInfo.YeniElx % 1000) - 200) * 10;
		}
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, (mUSER[tUserIndex].mAvatarInfo.YeniElx % 1000), 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;

	case 652: // %5 Binek Hapı 
		if (mUSER[tUserIndex].mAvatarInfo.aAnimalIndex < 10)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if ((mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] % 1000000) == 100000)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(2, tPage, tIndex, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] += 5000;
		if ((mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] % 1000000) > 100000)
		{
			mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] -= ((mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] % 1000000) - 100000);
		}
		tValue = mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10];
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10], 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 665:
		if ((mGAME.ReturnTribeRole(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe) == 0))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mGAME.CpTowerServer != TRUE)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mGAME.mCpTower.CpTowers[mGAME.CpTowerZoneIndex] != 0)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
		switch (tValue)
		{
		case 1:
			CpTowerNum = 589;
			CpToverVlue = 101;
			break;
		case 2:
			CpTowerNum = 593;
			CpToverVlue = 102;
			break;
		case 3:
			CpTowerNum = 597;
			CpToverVlue = 103;
			break;
		default:
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (!mSUMMON.SummonMonsterForCPTower(CpTowerNum, &mGAME.CpTowerYeri[0]))
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

		mGAME.mCpTower.CpTowers[mGAME.CpTowerZoneIndex] = CpToverVlue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1223: //Han para kutusu
		tRandomValue = rand() % 10000;
		if (tRandomValue < 100)
		{
			tValue = 635; //%15 Binek Kutusu
		}
		else if (tRandomValue > 100 && tRandomValue < 300)
		{
			tValue = 2249; //Cape Box
		}
		else if (tRandomValue > 300 && tRandomValue < 500)
		{
			tValue = 602; //Pet Box
		}
		else if (tRandomValue > 500 && tRandomValue < 800)
		{
			tValue = 579; //İksir
		}
		else if (tRandomValue > 800 && tRandomValue < 1000)
		{
			tValue = 1200; //Ünvan Silme
		}
		else if (tRandomValue > 1000 && tRandomValue < 2000)
		{
			tValue = 578; //İksir
		}
		else if (tRandomValue > 2000 && tRandomValue < 3000)
		{
			tValue = 509; //İksir
		}
		else if (tRandomValue > 3000 && tRandomValue < 4000)
		{
			tValue = 508; //İksir
		}
		else if (tRandomValue > 4000 && tRandomValue < 5000)
		{
			tValue = 507; //İksir
		}
		else if (tRandomValue > 5000 && tRandomValue < 6000)
		{
			tValue = 506; //İksir
		}
		else if (tRandomValue > 6000 && tRandomValue < 7000)
		{
			tValue = 1227; //+1 cp
		}
		else if (tRandomValue > 7000 && tRandomValue < 8000)
		{
			tValue = 1118; //2x cp
		}
		else if (tRandomValue > 8000 && tRandomValue < 9000)
		{
			tValue = 1102; //2. çanta
		}
		else
		{
			tValue = 1130; //2. depo
		}

		tITEM_INFO1 = mITEM.Search(tValue);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4],
			tITEM_INFO1->iIndex, tITEM_INFO1->iName, 0, 0);

		//Her kutu açılışında 50 kan veriliyor.
		mUSER[tUserIndex].mAvatarInfo.BloodStained += 50;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(121, mUSER[tUserIndex].mAvatarInfo.BloodStained);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 589://Pvp Box
		tRandomValue = tRandomValue = myrand(0, 10000);
		if (tRandomValue < 20)
		{
			switch (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe)
			{
			case 0:
				tValue = 2303;
				break;
			case 1:
				tValue = 2304;
				break;
			case 2:
				tValue = 2305;
				break;
			}
		}
		else if (tRandomValue < 45)
		{
			tValue = 1329;// Puma
		}
		else if (tRandomValue < 95)
		{
			tValue = 828;// SP Kabuk
		}
		else if (tRandomValue < 700)
		{
			tValue = 699;// GSS
		}
		else if (tRandomValue < 1700)
		{
			tValue = 1378;// Heaven Chest     
		}
		else if (tRandomValue < 2700)
		{
			tValue = 506; //İksir
		}
		else if (tRandomValue < 3700)
		{
			tValue = 507; //İksir
		}
		else if (tRandomValue < 4700)
		{
			tValue = 508; //İksir
		}
		else if (tRandomValue < 5700)
		{
			tValue = 509;// İksir
		}
		else if (tRandomValue < 6700)
		{
			tValue = 578;// İksir
		}
		else if (tRandomValue < 7700)
		{
			tValue = 579;// İksir
		}
		else if (tRandomValue < 9000)
		{
			tValue = 1448;// 500 CP
		}
		else if (tRandomValue < 9100)
		{
			tValue = 2169;//D PET BOX **kodu hala bilmiyom xd**
		}
		else {
			tValue = 1124;// Ferman
		}
		tITEM_INFO1 = mITEM.Search(tValue);
		if (tITEM_INFO1 == NULL)//Yanlış item gelirse dc at
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4],
			tITEM_INFO1->iIndex, tITEM_INFO1->iName, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 864://Skill Box
		int ItemLevel;
		int Type;
		switch (rand() % 4)
		{
		case 0:
			ItemLevel = 60;
			break;
		case 1:
			ItemLevel = 70;
			break;
		case 2:
			ItemLevel = 80;
			break;
		case 3:
			ItemLevel = 146;
			break;
		}

		switch (rand() % 2)
		{
		case 0:
			Type = 2;
			break;
		case 1:
			Type = 3;
			break;
		}

		tITEM_INFO1 = mITEM.GetSkillByTribeInfo(ItemLevel, Type, 5, mUSER[tUserIndex].mAvatarInfo.aPreviousTribe);
		if (tITEM_INFO1 == NULL)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		tValue = tITEM_INFO1->iIndex;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, 0, 0, tITEM_INFO1->iIndex, tITEM_INFO1->iName, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 891:
		if (mUSER[tUserIndex].mAvatarInfo.Title % 100 < 12)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.Title % 100 == 14)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe < 10000)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.Title += 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aTitle += 1;
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 10000;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe -= 10000;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe, 10000, 0, 0, 0, 0);
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1185: //5'li kabuk
		mUSER[tUserIndex].mAvatarInfo.ProtectionCharm += 5;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.ProtectionCharm, 5, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1103:
	case 1455:
		mUSER[tUserIndex].mAvatarInfo.ProtectionCharm += 1;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.ProtectionCharm, 1, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1026:// Dönüş kağıdı
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] < 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3]--;
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] < 1)
		{
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		}
		mAVATAR_OBJECT[tUserIndex].mCheckDeath = true;
		mAVATAR_OBJECT[tUserIndex].mCheckCount = 9;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;

	case 1041:
		mUSER[tUserIndex].mAvatarInfo.SuperiorPill += 180;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.SuperiorPill, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1043: //Ramadan Box    
		tRandomValue = myrand(0, 10000);

		if (tRandomValue < 50)
		{
			tValue = 823; // +1 Soket
		}
		else if (tRandomValue < 3010)
		{
			tValue = 983; //Mavi Taş
		}
		else if (tRandomValue < 3060)
		{
			tValue = 824; //+1 Döküm
		}
		else if (tRandomValue < 3160)
		{
			tValue = 984; //Beyaz Taş
		}
		else if (tRandomValue < 3300)
		{
			tValue = 1448; //500 CP
		}
		else if (tRandomValue < 3700)
		{
			tValue = 506; //iksir
		}
		else if (tRandomValue < 4200)
		{
			tValue = 507; //İksir
		}
		else if (tRandomValue < 5700)
		{
			tValue = 508; //iksir
		}
		else if (tRandomValue < 6200)
		{
			tValue = 509; //İksir
		}
		else if (tRandomValue < 6700)
		{
			tValue = 578; //İksir
		}
		else if (tRandomValue < 7200)
		{
			tValue = 579; //İksir
		}
		else if (tRandomValue < 8200)
		{
			tValue = 1072; //100m bar
		}
		else if (tRandomValue < 9200)
		{
			tValue = 1449; //100 CP
		}
		else
		{
			tValue = 1216; //OtoBuff
		}

		tITEM_INFO1 = mITEM.Search(tValue);
		if (tITEM_INFO1 == NULL)//Yanlış item gelirse dc at
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4],
			tITEM_INFO1->iIndex, tITEM_INFO1->iName, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1045:
		tMoney = (10000 + rand() % 10000) * 10;
		if (mUTIL.CheckOverMaximum(mUSER[tUserIndex].mAvatarInfo.aMoney, tMoney))
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aMoney += tMoney;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aMoney, tMoney, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aMoney);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1047:
		if (mUSER[tUserIndex].mAvatarInfo.aLevel1 < 113)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.SolemGrounds += 180;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.SolemGrounds, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1048:
		if (mUSER[tUserIndex].mAvatarInfo.aLevel1 < 100)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.GodTempleKey += 1;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.GodTempleKey, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1049:
		if (mUSER[tUserIndex].mAvatarInfo.aLevel1 < 145)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.EdgeOfTaiyan += 180;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.EdgeOfTaiyan, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1066: //[Book of Clear Fog]
		if ((tValue < 0) || (tValue > (MAX_SKILL_SLOT_NUM - 1)))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aSkill[tValue][0] < 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < 3; index01++)
		{
			for (index02 = 0; index02 < MAX_HOT_KEY_NUM; index02++)
			{
				if (mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][2] != 1)
				{
					continue;
				}
				if (mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][0] == mUSER[tUserIndex].mAvatarInfo.aSkill[tValue][0])
				{
					mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][0] = 0;
					mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][1] = 0;
					mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][2] = 0;
				}
			}
		}
		mUSER[tUserIndex].mAvatarInfo.aSkillPoint += mUSER[tUserIndex].mAvatarInfo.aSkill[tValue][1];
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aSkill[tValue][0], 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aSkill[tValue][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aSkill[tValue][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case  1069://ejder
		tRandomValue = myrand(0, 100);

		if (tRandomValue < 33)
		{
			tValue = 90787; //Pala
		}
		else if (tRandomValue < 66)
		{
			tValue = 90786; //Ağır kılıç
		}
		else
		{
			tValue = 90788; //Kopuz
		}

		tITEM_INFO1 = mITEM.Search(tValue);
		if (tITEM_INFO1 == NULL)//Yanlış item gelirse dc at
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, 0, 0, tITEM_INFO1->iIndex, tITEM_INFO1->iName, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case  1070://yılan
		tRandomValue = myrand(0, 100);

		if (tRandomValue < 33)
		{
			tValue = 90789; //Pala
		}
		else if (tRandomValue < 66)
		{
			tValue = 90790; //Ağır kılıç
		}
		else
		{
			tValue = 90791; //Kopuz
		}
		tITEM_INFO1 = mITEM.Search(tValue);
		if (tITEM_INFO1 == NULL)//Yanlış item gelirse dc at
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, 0, 0, tITEM_INFO1->iIndex, tITEM_INFO1->iName, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case  1071://Pars
		tRandomValue = myrand(0, 100);

		if (tRandomValue < 33)
		{
			tValue = 90793; //Pala
		}
		else if (tRandomValue < 66)
		{
			tValue = 90792; //Ağır kılıç
		}
		else
		{
			tValue = 90794; //Kopuz
		}
		tITEM_INFO1 = mITEM.Search(tValue);
		if (tITEM_INFO1 == NULL)//Yanlış item gelirse dc at
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, 0, 0, tITEM_INFO1->iIndex, tITEM_INFO1->iName, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case  1075: //[¹ß¼®Â÷(¹é)]
		if ((mGAME.ReturnTribeRole(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe) == 0) || (mUSER[tUserIndex].mAvatarInfo.aTribe != 0))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((mSERVER_INFO.mServerNumber != 2) && (mSERVER_INFO.mServerNumber != 3) && (mSERVER_INFO.mServerNumber != 4) && (mSERVER_INFO.mServerNumber != 7) && (mSERVER_INFO.mServerNumber != 8) && (mSERVER_INFO.mServerNumber != 9) && (mSERVER_INFO.mServerNumber != 12) && (mSERVER_INFO.mServerNumber != 13) && (mSERVER_INFO.mServerNumber != 14) && (mSERVER_INFO.mServerNumber != 141) && (mSERVER_INFO.mServerNumber != 142) && (mSERVER_INFO.mServerNumber != 143))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (!mSUMMON.SummonMonsterForTribeWeapon(543, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0]))
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, 0, 0, 0, "Katapult Kullanıldı", 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case  1076: //[¹ß¼®Â÷(ÆÐ)]
		if ((mGAME.ReturnTribeRole(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe) == 0) || (mUSER[tUserIndex].mAvatarInfo.aTribe != 1))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((mSERVER_INFO.mServerNumber != 2) && (mSERVER_INFO.mServerNumber != 3) && (mSERVER_INFO.mServerNumber != 4) && (mSERVER_INFO.mServerNumber != 7) && (mSERVER_INFO.mServerNumber != 8) && (mSERVER_INFO.mServerNumber != 9) && (mSERVER_INFO.mServerNumber != 12) && (mSERVER_INFO.mServerNumber != 13) && (mSERVER_INFO.mServerNumber != 14) && (mSERVER_INFO.mServerNumber != 141) && (mSERVER_INFO.mServerNumber != 142) && (mSERVER_INFO.mServerNumber != 143))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (!mSUMMON.SummonMonsterForTribeWeapon(544, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0]))
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, 0, 0, 0, "Katapult Kullanıldı", 0, 0); mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case  1077: //[¹ß¼®Â÷(Ç÷)]
		if ((mGAME.ReturnTribeRole(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe) == 0) || (mUSER[tUserIndex].mAvatarInfo.aTribe != 2))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((mSERVER_INFO.mServerNumber != 2) && (mSERVER_INFO.mServerNumber != 3) && (mSERVER_INFO.mServerNumber != 4) && (mSERVER_INFO.mServerNumber != 7) && (mSERVER_INFO.mServerNumber != 8) && (mSERVER_INFO.mServerNumber != 9) && (mSERVER_INFO.mServerNumber != 12) && (mSERVER_INFO.mServerNumber != 13) && (mSERVER_INFO.mServerNumber != 14) && (mSERVER_INFO.mServerNumber != 141) && (mSERVER_INFO.mServerNumber != 142) && (mSERVER_INFO.mServerNumber != 143))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (!mSUMMON.SummonMonsterForTribeWeapon(545, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0]))
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, 0, 0, 0, "Katapult Kullanıldı", 0, 0); mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case  1078: //[¹ß¼®Â÷(³¶)]
		if ((mGAME.ReturnTribeRole(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe) == 0) || (mUSER[tUserIndex].mAvatarInfo.aTribe != 3))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((mSERVER_INFO.mServerNumber != 2) && (mSERVER_INFO.mServerNumber != 3) && (mSERVER_INFO.mServerNumber != 4) && (mSERVER_INFO.mServerNumber != 7) && (mSERVER_INFO.mServerNumber != 8) && (mSERVER_INFO.mServerNumber != 9) && (mSERVER_INFO.mServerNumber != 12) && (mSERVER_INFO.mServerNumber != 13) && (mSERVER_INFO.mServerNumber != 14) && (mSERVER_INFO.mServerNumber != 141) && (mSERVER_INFO.mServerNumber != 142) && (mSERVER_INFO.mServerNumber != 143))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (!mSUMMON.SummonMonsterForTribeWeapon(546, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0]))
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, 0, 0, 0, "Katapult Kullanıldı", 0, 0); mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1101:
		tValue = mUTIL.ReturnAddDate(mUSER[tUserIndex].mAvatarInfo.aExpandStoreDate, 30);
		if (tValue == -1)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aExpandStoreDate = tValue;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aExpandStoreDate, tValue, 0, "", 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1102:
		tValue = mUTIL.ReturnAddDate(mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate, 7);
		if (tValue == -1)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate = tValue;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate, tValue, 0, "", 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1109: // Işınlanma kAĞIDI
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] < 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3]--;

		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] == 0)
		{
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		}
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 1118:
		mUSER[tUserIndex].mAvatarInfo.ScrollofLoyality += 30;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.ScrollofLoyality, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 1220:
		tRandomValue = myrand(0, 100);
		if (tRandomValue < 10)
		{
			tValue = 691; //5CP
		}
		else if (tRandomValue < 20) {
			tValue = 1166; //Aff
		}
		else if (tRandomValue < 30) {
			tValue = 828; //Sp döküm kabuğu
		}
		else if (tRandomValue < 40) {
			tValue = 1103; //Kabuk
		}
		else if (tRandomValue < 50) {
			tValue = 1218; //Döküm Tılsımı
		}
		else if (tRandomValue < 60) {
			tValue = 699; //Gss
		}
		else if (tRandomValue < 70) {
			tValue = 1237; //Kanat Koruyucu
		}
		else if (tRandomValue < 80) {
			tValue = 1378; //HeavenChest
		}
		else if (tRandomValue < 90) {
			tValue = 1118; //Cesaret Tılsımı
		}
		else if (tRandomValue < 93) {
			tValue = 589; //Pvp Chest
		}
		else if (tRandomValue < 95) {
			tValue = 1216; //1Günlük oto buff
		}
		else if (tRandomValue < 97) {
			tValue = 2169; //İlahi pet box
		}
		else if (tRandomValue < 100) {
			tValue = 635; //%15 binek
		}
		else {
			tValue = 891; //Title
		}
		tITEM_INFO1 = mITEM.Search(tValue);
		if (tITEM_INFO1 == NULL)//Yanlış item gelirse dc at
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, 0, 0, tITEM_INFO1->iIndex, tITEM_INFO1->iName, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 1491:
		if (mUSER[tUserIndex].mAvatarInfo.aEquip[8][2] == (mPAT.ReturnMaxPetExp(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0]) * 2))
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		tAddExp = (mPAT.ReturnMaxPetExp(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0])) * 0.03;
		if (mUSER[tUserIndex].mAvatarInfo.aEquip[8][2] > (mPAT.ReturnMaxPetExp(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0]) * 2))
		{
			mUSER[tUserIndex].mAvatarInfo.aEquip[8][2] = (mPAT.ReturnMaxPetExp(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0]) * 2);
		}

		if (mPAT.ReturnGrowStep(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0], (mUSER[tUserIndex].mAvatarInfo.aEquip[8][2] + tAddExp)) > mPAT.ReturnGrowStep(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0], mUSER[tUserIndex].mAvatarInfo.aEquip[8][2]))
		{
			mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 10, 0, 0, 0);
			mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		}
		mUSER[tUserIndex].mAvatarInfo.aEquip[8][2] += tAddExp;
		mAVATAR_OBJECT[tUserIndex].mDATA.aEquipForView[8][1] += tAddExp;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(14, mUSER[tUserIndex].mAvatarInfo.aEquip[8][2]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0]);
		if (tITEM_INFO1 == NULL)//Yanlış item gelirse dc at
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, 0, 0, tITEM_INFO1->iIndex, tITEM_INFO1->iName, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aEquip[8][2]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1434:
		mUSER[tUserIndex].mAvatarInfo.LifeOrDeath += 1;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.LifeOrDeath, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1492:
		if (mUSER[tUserIndex].mAvatarInfo.aEquip[8][2] == (mPAT.ReturnMaxPetExp(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0]) * 2))
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		tAddExp = (mPAT.ReturnMaxPetExp(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0])) * 0.01;
		if (mUSER[tUserIndex].mAvatarInfo.aEquip[8][2] > (mPAT.ReturnMaxPetExp(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0]) * 2))
		{
			mUSER[tUserIndex].mAvatarInfo.aEquip[8][2] = (mPAT.ReturnMaxPetExp(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0]) * 2);
		}

		if (mPAT.ReturnGrowStep(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0], (mUSER[tUserIndex].mAvatarInfo.aEquip[8][2] + tAddExp)) > mPAT.ReturnGrowStep(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0], mUSER[tUserIndex].mAvatarInfo.aEquip[8][2]))
		{
			mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 10, 0, 0, 0);
			mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		}
		mUSER[tUserIndex].mAvatarInfo.aEquip[8][2] += tAddExp;
		mAVATAR_OBJECT[tUserIndex].mDATA.aEquipForView[8][1] += tAddExp;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(14, mUSER[tUserIndex].mAvatarInfo.aEquip[8][2]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0]);
		if (tITEM_INFO1 == NULL)//Yanlış item gelirse dc at
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, 0, 0, tITEM_INFO1->iIndex, tITEM_INFO1->iName, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aEquip[8][2]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1124:
		mUSER[tUserIndex].mAvatarInfo.ScrollOfSeekers += 180;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.ScrollOfSeekers, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1129:
		tValue = mUTIL.ReturnAddDate(mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate, 30);
		if (tValue == -1)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate = tValue;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1130:
		tValue = mUTIL.ReturnAddDate(mUSER[tUserIndex].mAvatarInfo.aExpandStoreDate, 30);
		if (tValue == -1)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aExpandStoreDate = tValue;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aExpandStoreDate, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1142:
		if (mUSER[tUserIndex].mAvatarInfo.aLevel1 < 145)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aLevel2 < 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aVitality + mUSER[tUserIndex].mAvatarInfo.aStrength + mUSER[tUserIndex].mAvatarInfo.aKi + mUSER[tUserIndex].mAvatarInfo.aWisdom - 4);
		mUSER[tUserIndex].mAvatarInfo.aVitality = 1;
		mUSER[tUserIndex].mAvatarInfo.aStrength = 1;
		mUSER[tUserIndex].mAvatarInfo.aKi = 1;
		mUSER[tUserIndex].mAvatarInfo.aWisdom = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = 0;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, 0, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 1143:
		if (mUSER[tUserIndex].mAvatarInfo.aLevel1 < 145)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aLevel2 < 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((tValue < 1) || (tValue > 4))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch (tValue)
		{
		case 1:
			mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aStrength - 1);
			mUSER[tUserIndex].mAvatarInfo.aStrength = 1;
			break;
		case 2:
			mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aWisdom - 1);
			mUSER[tUserIndex].mAvatarInfo.aWisdom = 1;
			break;
		case 3:
			mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aVitality - 1);
			mUSER[tUserIndex].mAvatarInfo.aVitality = 1;
			break;
		case 4:
			mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aKi - 1);
			mUSER[tUserIndex].mAvatarInfo.aKi = 1;
			break;
		}
		mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = 0;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, 0, 0, 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 1145:
		mUSER[tUserIndex].mAvatarInfo.aAnimalTime += 180;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aAnimalTime, 0, 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aAnimalTime);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1146:
		mUSER[tUserIndex].mAvatarInfo.LuckyCombine += 3;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.LuckyCombine, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.LuckyCombine);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1147:
		mUSER[tUserIndex].mAvatarInfo.LuckyCombine += 2;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.LuckyCombine, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.LuckyCombine);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1148:
		mUSER[tUserIndex].mAvatarInfo.LuckyCombine += 1;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.LuckyCombine, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.LuckyCombine);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1218:
		mUSER[tUserIndex].mAvatarInfo.PreServeCharm += 1;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.PreServeCharm, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 1221:
		mUSER[tUserIndex].mAvatarInfo.DoubleMouthExp2x += 180;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.DoubleMouthExp2x, 0, 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1224: // Işınlanma kAĞIDI
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] < 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3]--;

		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] == 0)
		{
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		}
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 1166:
		mUSER[tUserIndex].mAvatarInfo.Cppc += 1;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.Cppc, 0, 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1167:
		mUSER[tUserIndex].mAvatarInfo.iGoldOrnamentRemainsTime += 240;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.iGoldOrnamentRemainsTime, 0, 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1171: //Gender Change Scroll
		mUSER[tUserIndex].mAvatarInfo.aGender = tValue % 10 / 1 - 1;
		mUSER[tUserIndex].mAvatarInfo.aHeadType = tValue % 100 / 10 - 1;
		mUSER[tUserIndex].mAvatarInfo.aFaceType = tValue % 1000 / 100 - 1;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);

		mAVATAR_OBJECT[tUserIndex].mDATA.aGender = mUSER[tUserIndex].mAvatarInfo.aGender;
		mAVATAR_OBJECT[tUserIndex].mDATA.aHeadType = mUSER[tUserIndex].mAvatarInfo.aHeadType;
		mAVATAR_OBJECT[tUserIndex].mDATA.aFaceType = mUSER[tUserIndex].mAvatarInfo.aFaceType;
		mTRANSFER.B_AVATAR_CHANGE_INFO_1(mAVATAR_OBJECT[tUserIndex].mIndex,
			mAVATAR_OBJECT[tUserIndex].mUniqueNumber,
			90,
			mUSER[tUserIndex].mAvatarInfo.aGender,
			mUSER[tUserIndex].mAvatarInfo.aHeadType,
			mUSER[tUserIndex].mAvatarInfo.aFaceType);
		mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		return;
	case 1190:
		mUSER[tUserIndex].mAvatarInfo.PetExpBoost += 180;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.PetExpBoost, 0, 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 1196:
		mUSER[tUserIndex].mAvatarInfo.HealtBoost += 30;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.HealtBoost, 0, 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 1199:
		mUSER[tUserIndex].mAvatarInfo.CritBoost += 30;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.CritBoost, 0, 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 1200: //Sağ tıklanabilir item Title Ayarla Cpsini hesapla
		if (mUSER[tUserIndex].mAvatarInfo.Title < 1)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

			return;
		}
		title = mUSER[tUserIndex].mAvatarInfo.Title % 100;
		for (int i = 0; i < title; i++)
		{
			AddCp += CpValue[i];
		}
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += AddCp;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe = mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe;
		mUSER[tUserIndex].mAvatarInfo.Title = 0;
		mAVATAR_OBJECT[tUserIndex].mDATA.aTitle = mUSER[tUserIndex].mAvatarInfo.Title;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe, AddCp, 0, 0, 0, 0);
		if (title == 13 || title == 14)
		{
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 891;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1201:
		tValue = mUTIL.ReturnAddDate(mUSER[tUserIndex].mAvatarInfo.AutoBuffScroll, 7);
		if (tValue == -1)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.AutoBuffScroll = tValue;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.AutoBuffScroll, 7, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 1216:
		tValue = mUTIL.ReturnAddDate(mUSER[tUserIndex].mAvatarInfo.AutoBuffScroll, 1);
		if (tValue == -1)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.AutoBuffScroll = tValue;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.AutoBuffScroll, 7, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 1222:
		mUSER[tUserIndex].mAvatarInfo.MountAbsorb += 180;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.MountAbsorb, 0, 0, 0, 0, 0);
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(78, mUSER[tUserIndex].mAvatarInfo.MountAbsorb);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1227:
		mUSER[tUserIndex].mAvatarInfo.WarriorScroll += 30;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.WarriorScroll, 0, 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1237:
		mUSER[tUserIndex].mAvatarInfo.WingProtectionRune += 1;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.WingProtectionRune, 0, 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1180:
		mUSER[tUserIndex].mAvatarInfo.BloodBoost += 1;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.SoulBoost, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1181:
		mUSER[tUserIndex].mAvatarInfo.SoulBoost += 1;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.SoulBoost, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1371:
		if (mUSER[tUserIndex].mAvatarInfo.BloodBoost >= 1)
		{
			mUSER[tUserIndex].mAvatarInfo.IslandOfBlood += 60;
			mUSER[tUserIndex].mAvatarInfo.BloodBoost--;
		}
		else
		{
			mUSER[tUserIndex].mAvatarInfo.IslandOfBlood += 30;
		}
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.IslandOfBlood, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1372:
		if (mUSER[tUserIndex].mAvatarInfo.SoulBoost >= 1)
		{
			mUSER[tUserIndex].mAvatarInfo.IslandOfSoulMReal1 += 60;
			mUSER[tUserIndex].mAvatarInfo.SoulBoost--;
		}
		else
		{
			mUSER[tUserIndex].mAvatarInfo.IslandOfSoulMReal1 += 30;
		}
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.IslandOfSoulMReal1, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1373:
		if (mUSER[tUserIndex].mAvatarInfo.SoulBoost >= 1)
		{
			mUSER[tUserIndex].mAvatarInfo.IslandOfSoulMReal2 += 60;
			mUSER[tUserIndex].mAvatarInfo.SoulBoost--;
		}
		else
		{
			mUSER[tUserIndex].mAvatarInfo.IslandOfSoulMReal2 += 30;
		}
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.IslandOfSoulMReal2, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1374:
		if (mUSER[tUserIndex].mAvatarInfo.SoulBoost >= 1)
		{
			mUSER[tUserIndex].mAvatarInfo.IslandOfSoulMReal3 += 60;
			mUSER[tUserIndex].mAvatarInfo.SoulBoost--;
		}
		else
		{
			mUSER[tUserIndex].mAvatarInfo.IslandOfSoulMReal3 += 30;
		}
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.IslandOfSoulMReal3, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1375:
		if (mUSER[tUserIndex].mAvatarInfo.SoulBoost >= 1)
		{
			mUSER[tUserIndex].mAvatarInfo.IslandOfSoulMReal4 += 60;
			mUSER[tUserIndex].mAvatarInfo.SoulBoost--;
		}
		else
		{
			mUSER[tUserIndex].mAvatarInfo.IslandOfSoulMReal4 += 30;
		}
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.IslandOfSoulMReal4, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1376:
		if (mUSER[tUserIndex].mAvatarInfo.SoulBoost >= 1)
		{
			mUSER[tUserIndex].mAvatarInfo.IslandOfSoulMReal5 += 60;
			mUSER[tUserIndex].mAvatarInfo.SoulBoost--;
		}
		else
		{
			mUSER[tUserIndex].mAvatarInfo.IslandOfSoulMReal5 += 30;
		}
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.IslandOfSoulMReal5, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1377:
		if (mUSER[tUserIndex].mAvatarInfo.SoulBoost >= 1)
		{
			mUSER[tUserIndex].mAvatarInfo.IslandOfSoulMReal6 += 60;
			mUSER[tUserIndex].mAvatarInfo.SoulBoost--;
		}
		else
		{
			mUSER[tUserIndex].mAvatarInfo.IslandOfSoulMReal6 += 30;
		}
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.IslandOfSoulMReal6, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case  1378: //Heaven Chest
		tRandomValue = rand() % 100;
		if (tRandomValue < 45)
		{
			switch (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe)
			{
			case 0:
				switch (rand() % 8)
				{
				case 0:
					tValue = 87077;// Ağır kılıç
					break;
				case 1:
					tValue = 87078;//Hafif Kılıç
					break;
				case 2:
					tValue = 87079;//Güç Topu
					break;
				case 3:
					tValue = 87080;//Zırh
					break;
				case 4:
					tValue = 87081;//Eldiven
					break;
				case 5:
					tValue = 87082;//Bot
					break;
				case 6:
					tValue = 87083;//Yüzük
					break;
				case 7:
					tValue = 87084;//Tılsım
					break;
				}
				break;
			case 1:
				switch (rand() % 8)
				{
				case 0:
					tValue = 87099;//Pala
					break;
				case 1:
					tValue = 87100;//Çift Bıçak
					break;
				case 2:
					tValue = 87101;//Kopuz
					break;
				case 3:
					tValue = 87102;//Zırh
					break;
				case 4:
					tValue = 87103;//Eldiven
					break;
				case 5:
					tValue = 87104;//Bot
					break;
				case 6:
					tValue = 87105;//Yüzük
					break;
				case 7:
					tValue = 87106;//Tılsım
					break;
				}
				break;
			case 2:
				switch (rand() % 8)
				{
				case 0:
					tValue = 87121;//Kısa Bıçak
					break;
				case 1:
					tValue = 87122;//Uzun Mızrak
					break;
				case 2:
					tValue = 87123;//Kama
					break;
				case 3:
					tValue = 87124;//Zırh
					break;
				case 4:
					tValue = 87125;//Eldiven
					break;
				case 5:
					tValue = 87126;//Bot
					break;
				case 6:
					tValue = 87127;//Yüzük
					break;
				case 7:
					tValue = 87128;//Tılsım
					break;
				}
				break;
			}
		}
		else
		{
			tValue = 1379;
		}
		tITEM_INFO1 = mITEM.Search(tValue);
		if (tITEM_INFO1 == NULL)//Yanlış item gelirse dc at
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], tITEM_INFO1->iIndex, tITEM_INFO1->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case  1379: //Earth Chest
		if (mUSER[tUserIndex].mAvatarInfo.aLevel2 < 1)
		{
			tItemLLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 - 5;
			if (tItemLLevel < 1)
			{
				tItemLLevel = 1;
			}
			tItemHLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 + 5;
			if (tItemHLevel > MAX_LIMIT_LEVEL_NUM)
			{
				tItemHLevel = MAX_LIMIT_LEVEL_NUM;
			}
		}
		else
		{
			tItemLLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2;
			tItemHLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2;
		}
		switch (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe)
		{
		case 0:
			tTribeItemList[0] = 7;
			tTribeItemList[1] = 8;
			tTribeItemList[2] = 9;
			tTribeItemList[3] = 10;
			tTribeItemList[4] = 11;
			tTribeItemList[5] = 12;
			tTribeItemList[6] = 13;
			tTribeItemList[7] = 14;
			tTribeItemList[8] = 15;
			break;
		case 1:
			tTribeItemList[0] = 7;
			tTribeItemList[1] = 8;
			tTribeItemList[2] = 9;
			tTribeItemList[3] = 10;
			tTribeItemList[4] = 11;
			tTribeItemList[5] = 12;
			tTribeItemList[6] = 16;
			tTribeItemList[7] = 17;
			tTribeItemList[8] = 18;
			break;
		case 2:
			tTribeItemList[0] = 7;
			tTribeItemList[1] = 8;
			tTribeItemList[2] = 9;
			tTribeItemList[3] = 10;
			tTribeItemList[4] = 11;
			tTribeItemList[5] = 12;
			tTribeItemList[6] = 19;
			tTribeItemList[7] = 20;
			tTribeItemList[8] = 21;
			break;
		}

		tRandomValue = rand() % 1000;
		if (tRandomValue < 500)
		{
			tItemType = 4;

		}
		else if (tRandomValue < 1000)
		{
			tItemType = 3;

		}
		tRandomValue = rand();
		tItemSort = tTribeItemList[(tRandomValue % 9)];
		tSearchNum = 0;
		tRandomValue = rand() % 2;
		switch (tRandomValue)
		{
		case 0:
			SetBonus = 1;
			break;
		case 1:
			SetBonus = 2;
			break;
		}
		if (tItemType == 4 && SetBonus == 1)
		{
			tItemType = 3;
			tRandomValue = rand() % 2;
			switch (tRandomValue)
			{
			case 0:
				SetBonus = 1;
				break;
			case 1:
				SetBonus = 2;
				break;
			}
		}
		while (tSearchNum < 10)
		{
			tRandomValue = rand();
			tITEM_INFO1 = mITEM.ReturnTalih((tItemLLevel + (tRandomValue % (tItemHLevel - tItemLLevel + 1))), tItemType, tItemSort, SetBonus);
			if (tITEM_INFO1)
			{
				if (((tITEM_INFO1->iEquipInfo[0] == 1) || ((tITEM_INFO1->iEquipInfo[0] - 2) == mUSER[tUserIndex].mAvatarInfo.aPreviousTribe)))
				{
					break;
				}
				tITEM_INFO1 = NULL;
				tSearchNum++;
			}
			else
			{
				tSearchNum++;
			}
		}
		if (tITEM_INFO1 == NULL)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		tValue = tITEM_INFO1->iIndex;
		if (tITEM_INFO1->iType == 4)
		{
			//mGAMELOG.GL_607_GAIN_SIN_ITEM(tUserIndex, 1, tITEM_INFO->iIndex, 0, 0, 100000003);
		}
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, 0, 0, tITEM_INFO1->iIndex, tITEM_INFO1->iName, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 100000003;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1445: //Kanat Kutusu

		tRandomValue = myrand(0, 10000);

		if (tRandomValue < 25) {
			switch (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe)
			{
			case 0:
				tValue = 2303;
				break;
			case 1:
				tValue = 2304;
				break;
			case 2:
				tValue = 2305;
				break;
			}
		}
		else if (tRandomValue < 125) {
			switch (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe)
			{
			case 0:
				tValue = 216;
				break;
			case 1:
				tValue = 217;
				break;
			case 2:
				tValue = 218;
				break;
			}
		}
		else if (tRandomValue < 1000) {
			tValue = 691;// 5 CP
		}
		else if (tRandomValue < 2000) {

			tValue = 695;// Beyaz Tüy     
		}
		else if (tRandomValue < 3000)
		{
			tValue = 1244; //Elmas
		}
		else if (tRandomValue < 4000)
		{
			tValue = 1118; //2x CP
		}
		else if (tRandomValue < 5000)
		{
			tValue = 1227; //Warrior's Scroll
		}
		else if (tRandomValue < 6000) {
			tValue = 1166;// Aff
		}
		else if (tRandomValue < 7000) {
			tValue = 1218;// Döküm Tılsımı
		}
		else if (tRandomValue < 8000) {
			tValue = 1130;// 2.banka
		}
		else if (tRandomValue < 9000) {
			tValue = 1102;// 2.çanta
		}
		else {
			tValue = 1124;// Ferman
		}

		//Her kutu açılışında 50 kan veriliyor.
		mUSER[tUserIndex].mAvatarInfo.BloodStained += 50;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(121, mUSER[tUserIndex].mAvatarInfo.BloodStained);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		tITEM_INFO1 = mITEM.Search(tValue);
		if (tITEM_INFO1 == NULL)//Yanlış item gelirse dc at
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3],
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], tITEM_INFO1->iIndex, tITEM_INFO1->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1447:
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 1000;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 1000;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe, 0, 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 691://10 Cp
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 5;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 5;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe, 0, 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 692://10 Cp
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 10;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 10;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe, 0, 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 1448:
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 500;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 500;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe, 0, 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1449:
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 100;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 100;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe, 0, 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1494: //Sağ tıklanabilir item Title Ayarla Cpsini hesapla
		if (mUSER[tUserIndex].mAvatarInfo.Title < 1)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

			return;
		}
		title = (mUSER[tUserIndex].mAvatarInfo.Title % 100);
		AddCp = 0;
		for (int i = 0; i < title; i++)
		{
			AddCp += CpValue[i];
		}
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += (AddCp * 0.7);
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe = mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe;
		mUSER[tUserIndex].mAvatarInfo.Title = 0;
		mAVATAR_OBJECT[tUserIndex].mDATA.aTitle = mUSER[tUserIndex].mAvatarInfo.Title;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe, (AddCp * 0.7), 0, 0, 0, 0);
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 2249://Cape Box
		tRandomValue = myrand(0, 100); //Yeni randım fonksiyonu örnek kod.
		if (tRandomValue < 1)
		{
			tValue = 1401;//Uktimate Cape
		}
		else if (tRandomValue < 4)
		{
			tValue = 1422;//Eritme Tılsımı
		}
		else if (tRandomValue < 7)
		{
			tValue = 506;//iksir 1
		}
		else if (tRandomValue < 10)
		{
			tValue = 507;//iksir 2
		}
		else if (tRandomValue < 13)
		{
			tValue = 508;//iksir 3
		}
		else if (tRandomValue < 16)
		{
			tValue = 509;//iksir 4
		}
		else if (tRandomValue < 18)
		{
			tValue = 578;//iksir 5
		}
		else if (tRandomValue < 20)
		{
			tValue = 579;//iksir 6
		}
		else if (tRandomValue < 25)
		{
			tValue = 1124;//Ferman
		}
		else if (tRandomValue < 30)
		{
			tValue = 1130;//1. banka
		}
		else if (tRandomValue < 35)
		{
			tValue = 1102;//1. depo
		}
		else if (tRandomValue < 55)
		{
			tValue = 1072;//Işınlanma Kağıdı
		}
		else if (tRandomValue < 70)
		{
			tValue = 1023;//Plat
		}
		else if (tRandomValue < 79)
		{
			tValue = 576;//Kalıp
		}
		else if (tRandomValue < 89)
		{
			tValue = 983;//Daş
		}
		else
		{
			tValue = 1022;//Eritme
		}
		tRandomValue = myrand(0, 150);
		if (tRandomValue < 1)
		{
			tValue = 901;//8.Bk Birleştirme
		}
		tITEM_INFO1 = mITEM.Search(tValue);
		if (tITEM_INFO1 == NULL)//Yanlış item gelirse dc at
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		if (tITEM_INFO1->iSort == 99)
		{
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 1;
		}
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4],
			tITEM_INFO1->iIndex, tITEM_INFO1->iName, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1894://Hisar
		mUSER[tUserIndex].mAvatarInfo.Hisar += 1;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.Hisar, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.Hisar);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 2169: //iLAH Pet Kutusu
		tRandomValue = myrand(0, 100);

		if (tRandomValue < 10)
		{
			tValue = 1312;
		}
		if (tRandomValue < 20)
		{
			tValue = 2133;
		}
		if (tRandomValue < 30)
		{
			tValue = 2144;
		}
		if (tRandomValue < 40)
		{
			tValue = 2160;
		}
		else if (tRandomValue < 70)
		{
			tValue = 1311;
		}
		else
		{
			tValue = 1310;
		}

		tITEM_INFO1 = mITEM.Search(tValue);
		if (tITEM_INFO1 == NULL)//Yanlış item gelirse dc at
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4],
			tITEM_INFO1->iIndex, tITEM_INFO1->iName, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 2334:
	case 2393:
		mUSER[tUserIndex].mAvatarInfo.LifeOrDeath += 1;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.LifeOrDeath, 0, 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 2448:
		tRandomValue = (4 + (rand() % 3));
		index02 = 1;
		for (index01 = 1; index01 < tRandomValue; index01++)
		{
			tITEM_INFO1 = mITEM.Search(531);
			if (tITEM_INFO1 == NULL)
			{
				break;
			}
			if (mUTIL.FindEmptyInvenForItem(tUserIndex, tITEM_INFO1, iInvenPage1[index01], iInvenSlot1[index01]) == false)
			{
				break;
			}
			iInvenIndex1[index01] = mUTIL.GetEmptyInvenSlotIndex(tUserIndex, iInvenPage1[index01]);
			if (iInvenSlot == -1)
			{
				break;
			}
			index02++;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iInvenPage1[index01]][iInvenIndex1[index01]][0] = 531;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iInvenPage1[index01]][iInvenIndex1[index01]][1] = iInvenSlot1[index01] % 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iInvenPage1[index01]][iInvenIndex1[index01]][2] = iInvenSlot1[index01] / 8;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iInvenPage1[index01]][iInvenIndex1[index01]][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iInvenPage1[index01]][iInvenIndex1[index01]][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iInvenPage1[index01]][iInvenIndex1[index01]][5] = 0;
		}
		if (index01 != tRandomValue)
		{
			for (index01 = 1; index01 < index02; index01++)
			{
				mUSER[tUserIndex].mAvatarInfo.aInventory[iInvenPage1[index01]][iInvenIndex1[index01]][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[iInvenPage1[index01]][iInvenIndex1[index01]][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[iInvenPage1[index01]][iInvenIndex1[index01]][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[iInvenPage1[index01]][iInvenIndex1[index01]][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[iInvenPage1[index01]][iInvenIndex1[index01]][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[iInvenPage1[index01]][iInvenIndex1[index01]][5] = 0;
			}
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		for (index01 = 1; index01 < tRandomValue; index01++)
		{
			mTRANSFER.B_ITEM_SEND(0, 531, iInvenPage1[index01], iInvenIndex1[index01], iInvenSlot1[index01]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 531;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, tRandomValue, 0, 0, "", 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, 531);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 1125: //Han para kutusu Pet Kutusu
		tRandomValue = rand() % 10000;
		if (tRandomValue < 60)
		{
			tValue = 2169; //%15 Binek Kutusu
		}
		else if (tRandomValue > 60 && tRandomValue < 150)
		{
			tValue = 1124; //Ferman
		}
		else if (tRandomValue > 150 && tRandomValue < 340)
		{
			tValue = 2249; //Cape Box
		}
		else if (tRandomValue > 340 && tRandomValue < 500)
		{
			tValue = 602; //Pet Box
		}
		else if (tRandomValue > 500 && tRandomValue < 800)
		{
			tValue = 579; //İksir
		}
		else if (tRandomValue > 800 && tRandomValue < 1000)
		{
			tValue = 1200; //Ünvan Silme
		}
		else if (tRandomValue > 1000 && tRandomValue < 2000)
		{
			tValue = 578; //İksir
		}
		else if (tRandomValue > 2000 && tRandomValue < 3000)
		{
			tValue = 509; //İksir
		}
		else if (tRandomValue > 3000 && tRandomValue < 4000)
		{
			tValue = 508; //İksir
		}
		else if (tRandomValue > 4000 && tRandomValue < 5000)
		{
			tValue = 507; //İksir
		}
		else if (tRandomValue > 5000 && tRandomValue < 6000)
		{
			tValue = 506; //İksir
		}
		else if (tRandomValue > 6000 && tRandomValue < 7000)
		{
			tValue = 1227; //+1 cp
		}
		else if (tRandomValue > 7000 && tRandomValue < 8000)
		{
			tValue = 1118; //2x cp
		}
		else if (tRandomValue > 8000 && tRandomValue < 9000)
		{
			tValue = 1102; //2. çanta
		}
		else
		{
			tValue = 1130; //2. depo
		}

		tITEM_INFO1 = mITEM.Search(tValue);
		if (tITEM_INFO1 == NULL)//Yanlış item gelirse dc at
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4],
			tITEM_INFO1->iIndex, tITEM_INFO1->iName, 0, 0);

		//Her kutu açılışında 50 kan veriliyor.
		mUSER[tUserIndex].mAvatarInfo.BloodStained += 50;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(121, mUSER[tUserIndex].mAvatarInfo.BloodStained);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 1446: //Pelerin	
		tRandomValue = rand() % 10000;
		if (tRandomValue < 50)
		{
			tValue = 1403; //Pelerin
		}
		else if (tRandomValue < 300)
		{
			tValue = 983; //Mavi yükseltme taşı
		}
		else if (tRandomValue < 500)
		{
			tValue = 1216; //1 Günlük Otobuff
		}
		else if (tRandomValue < 1500)
		{
			tValue = 506; //iksir
		}
		else if (tRandomValue < 2500)
		{
			tValue = 507; //İksir
		}
		else if (tRandomValue < 3500)
		{
			tValue = 508; //iksir
		}
		else if (tRandomValue < 4500)
		{
			tValue = 509; //İksir
		}
		else if (tRandomValue < 5500)
		{
			tValue = 578; //İksir
		}
		else if (tRandomValue < 6500)
		{
			tValue = 579; //İksir
		}
		else if (tRandomValue < 7500)
		{
			tValue = 1227; //+1 cp
		}
		else if (tRandomValue < 8500)
		{
			tValue = 1118; //2x cp
		}
		else if (tRandomValue < 9000)
		{
			tValue = 1124; //Ferman
		}
		else if (tRandomValue < 9500)
		{
			tValue = 2249; //Cape Box
		}
		else
		{
			tValue = 602; //Pet Box
		}

		tITEM_INFO1 = mITEM.Search(tValue);
		if (tITEM_INFO1 == NULL)//Yanlış item gelirse dc at
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4],
			tITEM_INFO1->iIndex, tITEM_INFO1->iName, 0, 0);

		//Her kutu açılışında 50 kan veriliyor.
		mUSER[tUserIndex].mAvatarInfo.BloodStained += 50;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(121, mUSER[tUserIndex].mAvatarInfo.BloodStained);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 2337: //Title ticket kutusu	
		tRandomValue = myrand(0, 10000);
		if (tRandomValue < 80)
		{
			tValue = 1218; // Döküm Tılsımı
		}
		else if (tRandomValue < 3060)
		{
			tValue = 983; //Mavi Taş
		}
		else if (tRandomValue < 3160)
		{
			tValue = 984; //Beyaz Taş
		}
		else if (tRandomValue < 3300)
		{
			tValue = 891; //Title Ticket
		}
		else if (tRandomValue < 3700)
		{
			tValue = 506; //iksir
		}
		else if (tRandomValue < 4200)
		{
			tValue = 507; //İksir
		}
		else if (tRandomValue < 5700)
		{
			tValue = 508; //iksir
		}
		else if (tRandomValue < 6200)
		{
			tValue = 509; //İksir
		}
		else if (tRandomValue < 6700)
		{
			tValue = 578; //İksir
		}
		else if (tRandomValue < 7200)
		{
			tValue = 579; //İksir
		}
		else if (tRandomValue < 8200)
		{
			tValue = 1072; //100m bar
		}
		else if (tRandomValue < 9200)
		{
			tValue = 1124; //Ferman
		}
		else
		{
			tValue = 1216; //OtoBuff
		}

		tITEM_INFO1 = mITEM.Search(tValue);
		if (tITEM_INFO1 == NULL)//Yanlış item gelirse dc at
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4],
			tITEM_INFO1->iIndex, tITEM_INFO1->iName, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 530: //Yalor Box
		tRandomValue = myrand(0, 10000);
		if (tRandomValue < 2000)
		{
			tValue = 1218;//Döküm Kabuğu
		}
		else if (tRandomValue < 3000)
		{
			tValue = 1447;//1K cp
		}
		else if (tRandomValue < 4000)
		{
			tValue = 1237;//Kanat Koruyucu
		}
		else if (tRandomValue < 5000)
		{
			tValue = 552;//Event Box
		}
		else if (tRandomValue < 6000)
		{
			tValue = 1226;//Reverse Pill
		}
		else if (tRandomValue < 7000)
		{
			tValue = 699;//Döküm 1-3
		}
		else if (tRandomValue < 8000)
		{
			tValue = 1166;//Aff
		}
		else if (tRandomValue < 9000)
		{
			tValue = 828;//LessDecress
		}
		else if (tRandomValue < 9500)
		{
			tValue = 1133;// Name Change
		}
		else if (tRandomValue < 9600)
		{
			tValue = 1142;// Stat reset
		}
		else if (tRandomValue < 9700)
		{
			tValue = 635;// Mount Box 15%
		}
		else if (tRandomValue < 9800)
		{
			tValue = 2169;// Daity Pet Kutusu
		}
		else if (tRandomValue < 9900)
		{
			tValue = 891;// Titkle Ticket
		}
		else
		{
			tValue = 903;// MTS
		}

		tITEM_INFO1 = mITEM.Search(tValue);
		if (tITEM_INFO1 == NULL)//Yanlış item gelirse dc at
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4],
			tITEM_INFO1->iIndex, tITEM_INFO1->iName, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 552: //Event Box
		tRandomValue = myrand(0, 10000);
		if (tRandomValue < 1000)
		{
			tValue = 699;//1-3 Döküm
		}
		else if (tRandomValue < 2000)
		{
			tValue = 502;//Upgrade Stone
		}
		else if (tRandomValue < 3000)
		{
			tValue = 503;//Upgrade Stone
		}
		else if (tRandomValue < 4000)
		{
			tValue = 2337;//Title Ticket Box
		}
		else if (tRandomValue < 5000)
		{
			tValue = 1199;//Kritik Hasar tılsımı
		}
		else if (tRandomValue < 6000)
		{
			tValue = 589;//PvP Box
		}
		else if (tRandomValue < 7000)
		{
			tValue = 1223;//God Lucky Bag % 15 binek kutusu
		}
		else if (tRandomValue < 8000)
		{
			tValue = 504;//Upgrade Stone
		}
		else if (tRandomValue < 9000)
		{
			tValue = 984;// White Jade
		}
		else if (tRandomValue < 9300)
		{
			tValue = 1118;// Cesaret Tılsımı
		}
		else if (tRandomValue < 9600)
		{
			tValue = 501;//Upgrade Stone
		}
		else if (tRandomValue < 9950)
		{
			tValue = 635;// 15% Mount Box
		}
		else
		{
			tValue = 1124;// Deity Pet Bag
		}
		tITEM_INFO1 = mITEM.Search(tValue);
		if (tITEM_INFO1 == NULL)//Yanlış item gelirse dc at
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4],
			tITEM_INFO1->iIndex, tITEM_INFO1->iName, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 828:
		mUSER[tUserIndex].mAvatarInfo.LessDecressScroll += 1;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.LifeOrDeath, 0, 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 2399:
		tRandomValue = myrand(0, 4);

		switch (tRandomValue)
		{
		case 0:
			tValue = 501;
			break;
		case 1:
			tValue = 502;
			break;
		case 2:
			tValue = 503;
			break;
		case 3:
			tValue = 504;
			break;
		default:
			tValue = 504;
			break;
		}

		tITEM_INFO1 = mITEM.Search(tValue);
		if (tITEM_INFO1 == NULL)//Yanlış item gelirse dc at
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4],
			tITEM_INFO1->iIndex, tITEM_INFO1->iName, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		return;
	case 2462:
		if (mUSER[tUserIndex].mAvatarInfo.aLevel2 != 12)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		if (mUSER[tUserIndex].mAvatarInfo.SkillIncreaseCritHit == 12)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		if (mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 != 1481117817)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		mAVATAR_OBJECT[tUserIndex].mDATA.aRebirth += 1;
		mUSER[tUserIndex].mAvatarInfo.SkillIncreaseCritHit += 1;
		mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 = 0;

		if (mAVATAR_OBJECT[tUserIndex].mDATA.aRebirth < 5)
		{
			mUSER[tUserIndex].mAvatarInfo.LifeOrDeath += 3;
		}

		mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 14, mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe, mUSER[tUserIndex].mAvatarInfo.SkillIncreaseCritHit, 0);
		mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1);

		if (mUSER[tUserIndex].mAvatarInfo.SkillIncreaseCritHit == 12)
			SendRebirthNotice(tUserIndex);

		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.SkillIncreaseCritHit, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, 0);

		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		break;
	case 2068: //Puma kutusu
		tRandomValue = myrand(0, 10000);

		if (tRandomValue < 50)
		{
			tValue = 1329; //Puma
		}
		else if (tRandomValue < 200)
		{
			tValue = 2462; //Rebirth Pill
		}
		else if (tRandomValue < 400)
		{
			tValue = 699; //GSS
		}
		else if (tRandomValue < 800)
		{
			tValue = 984; //Beyaz Taş
		}
		else if (tRandomValue < 1000)
		{
			tValue = 1145; //Canavar Hapı
		}
		else if (tRandomValue < 2000)
		{
			tValue = 1216; // Auto Buff 1d
		}
		else if (tRandomValue < 3000)
		{
			tValue = 1124; //Sos
		}
		else if (tRandomValue < 4000)
		{
			tValue = 1218; //Dokum Tilsimi
		}
		else if (tRandomValue < 5000)
		{
			tValue = 1222; //Binek absorb
		}
		else if (tRandomValue < 6000)
		{
			tValue = 983; //Mavi Taş
		}
		else if (tRandomValue < 7000)
		{
			tValue = 1244; //Elmas
		}
		else if (tRandomValue < 8000)
		{
			tValue = 1118; //+1 CP
		}
		else if (tRandomValue < 9000)
		{
			tValue = 1102; //2. çanta
		}
		else
		{
			tValue = 1130; //2. depo
		}

		tITEM_INFO1 = mITEM.Search(tValue);
		if (tITEM_INFO1 == NULL)//Yanlış item gelirse dc at
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4],
			tITEM_INFO1->iIndex, tITEM_INFO1->iName, 0, 0);

		//Her kutu açılışında 50 kan veriliyor.
		mUSER[tUserIndex].mAvatarInfo.BloodStained += 50;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(121, mUSER[tUserIndex].mAvatarInfo.BloodStained);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 970:
		if (mUSER[tUserIndex].mAvatarInfo.aAnimalIndex < 0 || mUSER[tUserIndex].mAvatarInfo.aAnimalIndex >9)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		switch (mUSER[tUserIndex].mAvatarInfo.aAnimal[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex])
		{
		case 1301:
		case 1302:
		case 1303:
		case 1304:
		case 1305:
		case 1306:
		case 1307:
		case 1308:
		case 1309:
		case 1313:
		case 1314:
		case 1315:
		case 1316:
		case 1317:
		case 1318:
		case 1319:
		case 1320:
		case 1321:
		case 1322:
		case 1323:
		case 1324:
		case 1325:
		case 1326:
		case 1327:
		case 1328:
		case 1329:
		case 1330:
		case 1331:
			break;
		default:
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = mUSER[tUserIndex].mAvatarInfo.aAnimal[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mUSER[tUserIndex].mExtraAvatarInfo.AnimalTransferInventory[tPage][tIndex] = mUSER[tUserIndex].mAvatarInfo.AnimalStat[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex];
		mUSER[tUserIndex].mAvatarInfo.aAnimal[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex] = 0;
		mUSER[tUserIndex].mAvatarInfo.AnimalExp[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex] = 0;
		mUSER[tUserIndex].mAvatarInfo.AnimalStat[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex] = 0;
		AnimalIndex = mUSER[tUserIndex].mAvatarInfo.aAnimalIndex;
		mUSER[tUserIndex].mAvatarInfo.aAnimalIndex = -1;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, AnimalIndex);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
		//400 iksirler
	case 801:
		if (mUSER[tUserIndex].mAvatarInfo.aEatLifePotion < 200 || mUSER[tUserIndex].mAvatarInfo.aEatLifePotion >= 400)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.SkillIncreaseCritHit != 12)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aEatLifePotion += 1;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aEatLifePotion, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 802:
		if (mUSER[tUserIndex].mAvatarInfo.aEatManaPotion < 200 || mUSER[tUserIndex].mAvatarInfo.aEatManaPotion >= 400)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.SkillIncreaseCritHit != 12)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aEatManaPotion += 1;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.aEatManaPotion, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 803:
		if (mUSER[tUserIndex].mAvatarInfo.StrElx < 200 || mUSER[tUserIndex].mAvatarInfo.StrElx >= 400)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.SkillIncreaseCritHit != 12)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.StrElx += 1;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.StrElx, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 804:
		if (mUSER[tUserIndex].mAvatarInfo.AgiElx < 200 || mUSER[tUserIndex].mAvatarInfo.AgiElx >= 400)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.SkillIncreaseCritHit != 12)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.AgiElx += 1;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.AgiElx, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 805:
		if ((mUSER[tUserIndex].mAvatarInfo.YeniElx / 1000) < 200 || (mUSER[tUserIndex].mAvatarInfo.YeniElx / 1000) >= 400)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.SkillIncreaseCritHit != 12)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.YeniElx += 1000;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, (mUSER[tUserIndex].mAvatarInfo.YeniElx / 1000), 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 806:
		if ((mUSER[tUserIndex].mAvatarInfo.YeniElx % 1000) < 200 || (mUSER[tUserIndex].mAvatarInfo.YeniElx % 1000) >= 400)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.SkillIncreaseCritHit != 12)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.YeniElx += 1;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, (mUSER[tUserIndex].mAvatarInfo.YeniElx % 1000), 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 713://Thye Fortress
		mUSER[tUserIndex].mAvatarInfo.TheFortress += 30;
		mGAMELOG.GL_USE_INVENTORY_ITEM(tUserIndex, tITEM_INFO->iIndex, tITEM_INFO->iName, mUSER[tUserIndex].mAvatarInfo.TheFortress, 0, 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
		return;
	default:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
}
