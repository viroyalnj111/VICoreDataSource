//
//  GFDataSource.h
//  GFCoreDataSource
//
//  Created by guofengld on 16/12/12.
//  Copyright © 2016年 guofengld. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "NSManagedObject+GFCoreDataSource.h"

NS_ASSUME_NONNULL_BEGIN

typedef void (^CommonBlock)(BOOL success, NSDictionary * _Nullable info);

@class GFDataSource;
@protocol GFDataSource;

@protocol GFDataSourceDelegate <NSObject>

//This method is needed
- (void)dataSource:(id<GFDataSource>)dataSource didChangeContentForKey:(nullable NSString *)key;

@optional

- (void)dataSource:(id<GFDataSource>)dataSource willChangeContentForKey:(nullable NSString *)key;

- (void)dataSource:(id<GFDataSource>)dataSource
  didChangeSection:(id<NSFetchedResultsSectionInfo>)sectionInfo
           atIndex:(NSUInteger)sectionIndex
     forChangeType:(NSFetchedResultsChangeType)type
            forKey:(nullable NSString *)key;

- (void)dataSource:(id<GFDataSource>)dataSource
   didChangeObject:(id)anObject
       atIndexPath:(NSIndexPath *)indexPath
     forChangeType:(NSFetchedResultsChangeType)type
      newIndexPath:(NSIndexPath *)newIndexPath
            forKey:(nullable NSString *)key;

@end

@protocol GFDataSource <NSObject>

- (NSInteger)numberOfSectionsForKey:(NSString *)key;
- (NSInteger)numberOfItemsForKey:(NSString *)key inSection:(NSInteger)section;
- (nullable id)objectAtIndexPath:(NSIndexPath *)indexPath forKey:(NSString *)key;
- (nullable id<NSFetchedResultsSectionInfo>)sectionInfoForSection:(NSInteger)section key:(NSString *)key;
- (NSArray *)allObjectsForKey:(NSString *)key;

@end

@interface GFDataSource : NSObject < GFDataSource >

@property (nonatomic, weak)     id<GFDataSourceDelegate>        delegate;
@property (nonatomic, readonly) NSManagedObjectContext          *managedObjectContext;
@property (nonatomic, readonly) NSPersistentStoreCoordinator    *persistentStoreCoordinator;

+ (instancetype)sharedClient;

- (instancetype)initWithManagedObjectContext:(NSManagedObjectContext *)managedContex
                                 coordinator:(nullable NSPersistentStoreCoordinator *)coordinator;

- (void)registerDelegate:(id<GFDataSourceDelegate>)delegate
                  entity:(nonnull NSString *)entityName
               predicate:(nullable NSPredicate *)predicate
         sortDescriptors:(nonnull NSArray<NSSortDescriptor *>*)sortDescriptors
      sectionNameKeyPath:(nullable NSString *)sectionNameKeyPath
                     key:(NSString *)key;

- (NSFetchedResultsController *)fetchedResultsControllerForKey:(NSString *)key;
- (id<GFDataSourceDelegate>)delegateForKey:(NSString *)key;
- (nullable NSString *)keyForController:(NSFetchedResultsController *)controller;
- (id<GFDataSourceDelegate>)delegateForController:(NSFetchedResultsController *)controller;
- (NSEnumerator <NSFetchedResultsController *> *)fetchedResultsControllerEnumerator;

- (void)addObject:(id)object
       entityName:(NSString *)entityName;

- (void)addObjects:(NSArray *)array
        entityName:(NSString *)entityName
          syncAll:(BOOL)syncAll
     syncPredicate:(nullable NSPredicate *)predicate;

- (void)deleteObject:(id)object;

- (void)deleteObjects:(NSArray *)array;

- (NSManagedObject *)onAddObject:(id)object managedObjectContext:(NSManagedObjectContext *)managedObjectContex;

- (void)onDeleteObject:(id)object managedObjectContext:(NSManagedObjectContext *)managedObjectContex;

- (void)didReceiveMemoryWarning;

@end

NS_ASSUME_NONNULL_END