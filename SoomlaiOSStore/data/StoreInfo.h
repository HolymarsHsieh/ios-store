/*
 * Copyright (C) 2012 Soomla Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#import <Foundation/Foundation.h>
#import "IStoreAssets.h"

@class VirtualCategory;
@class VirtualCurrency;
@class VirtualGood;
@class VirtualCurrencyPack;
@class NonConsumableItem;
@class VirtualItem;
@class PurchasableVirtualItem;
@class UpgradeVG;

/**
 * This class holds the store's meta data including:
 * - Virtual Currencies
 * - Virtual Currency Packs
 * - All kinds of Virtual Goods
 * - Virtual Categories
 * - NonConsumables
 */
@interface StoreInfo : NSObject{
    @private
    NSMutableDictionary* virtualItems;
    NSMutableDictionary* purchasableItems;
    NSMutableDictionary* goodsCategories;
    NSMutableDictionary* goodsUpgrades;
    @public
    NSMutableArray* virtualCurrencies;
    NSMutableArray* virtualGoods;
    NSMutableArray* virtualCurrencyPacks;
    NSMutableArray* nonConsumableItems;
    NSMutableArray* virtualCategories;
}

@property (nonatomic, retain) NSMutableArray* virtualCurrencies;
@property (nonatomic, retain) NSMutableArray* virtualGoods;
@property (nonatomic, retain) NSMutableArray* virtualCurrencyPacks;
@property (nonatomic, retain) NSMutableArray* nonConsumableItems;
@property (nonatomic, retain) NSMutableArray* virtualCategories;
@property (nonatomic, retain) NSMutableDictionary* virtualItems;
@property (nonatomic, retain) NSMutableDictionary* purchasableItems;
@property (nonatomic, retain) NSMutableDictionary* goodsCategories;
@property (nonatomic, retain) NSMutableDictionary* goodsUpgrades;

+ (StoreInfo*)getInstance;

/**
 * This function initializes StoreInfo. On first initialization, when the
 * database doesn't have any previous version of the store metadata, StoreInfo
 * is being loaded from the given IStoreAssets. After the first initialization,
 * StoreInfo will be initialized from the database.
 *
 * IMPORTANT: If you want to override the current StoreInfo, you'll have to bump the version of your
 * implementation of IStoreAssets in order to remove the metadata when the application loads.
 * (bumping the version is done by returning a higher number in IStoreAssets:getVersion.
 */
- (void)initializeWithIStoreAssets:(id <IStoreAssets>)storeAssets;

/**
 * Initializes StoreInfo from the database. This action should be performed only once during the lifetime of
 * a session of the game. StoreController automatically initializes StoreInfo. Don't do it if you don't know what
 * you're doing.
 * return success.
 */
- (BOOL)initializeFromDB;
- (NSDictionary*)toDictionary;


/**
 * A utility function to retrieve a single VirtualItem that resides in the meta data.
 *
 * itemId is the itemId of the required VirtualItem.
 *
 * throws VirtualItemNotFoundException when the given itemId was not found.
 */
- (VirtualItem*)virtualItemWithId:(NSString*)itemId;

/**
 * A utility function to retrieve a single PurchasableVirtualItem that resides in the meta data.
 *
 * IMPORTANT: The retrieved PurchasableVirtualItems are only those which has a purchaseType of PurchaseWithMarket.
 * (This is why we fetch here with productId)
 *
 * productId the productId of the required PurchasableVirtualItem.
 *
 * throws VirtualItemNotFoundException when the given productId was not found.
 */
- (PurchasableVirtualItem*)purchasableItemWithProductId:(NSString*)productId;

/**
 * A utility function to retrieve a single VirtualCategory for a given VirtualGood itemId.
 *
 * goodItemId is the virtualGood in the category.
 *
 * returns a VirtualCategory for the given VirtualGood.
 *
 * throws VirtualItemNotFoundException when the given goodItemId was not found.
 */
- (VirtualCategory*)categoryForGoodWithItemId:(NSString*)goodItemId;

/**
 * A utility function to retrieve a first UpgradeVG for a given VirtualGood itemId.
 * goodItemId is the VirtualGood we're searching the upgrade for.
 */
- (UpgradeVG*)firstUpgradeForGoodWithItemId:(NSString*)goodItemId;

/**
 * A utility function to retrieve a last UpgradeVG for a given VirtualGood itemId.
 * goodItemId is the VirtualGood we're searching the upgrade for.
 */
- (UpgradeVG*)lastUpgradeForGoodWithItemId:(NSString*)goodItemId;

/**
 * A utility function to retrieve all UpgradeVGs for a given VirtualGood itemId.
 * goodItemId is the VirtualGood we're searching the upgrades for.
 */
- (NSArray*)upgradesForGoodWithItemId:(NSString*)goodItemId;

- (NSArray*)allProductIds;
- (BOOL)goodHasUpgrades:(NSString*)goodItemId;
- (void)save;
- (void)save:(VirtualItem*)virtualItem;
- (void)replaceVirtualItem:(VirtualItem*)virtualItem;
@end
