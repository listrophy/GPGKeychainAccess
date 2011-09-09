/*
 Copyright © Roman Zechmeister, 2011
 
 Dieses Programm ist freie Software. Sie können es unter den Bedingungen 
 der GNU General Public License, wie von der Free Software Foundation 
 veröffentlicht, weitergeben und/oder modifizieren, entweder gemäß 
 Version 3 der Lizenz oder (nach Ihrer Option) jeder späteren Version.
 
 Die Veröffentlichung dieses Programms erfolgt in der Hoffnung, daß es Ihnen 
 von Nutzen sein wird, aber ohne irgendeine Garantie, sogar ohne die implizite 
 Garantie der Marktreife oder der Verwendbarkeit für einen bestimmten Zweck. 
 Details finden Sie in der GNU General Public License.
 
 Sie sollten ein Exemplar der GNU General Public License zusammen mit diesem 
 Programm erhalten haben. Falls nicht, siehe <http://www.gnu.org/licenses/>.
*/

#import <Libmacgpg/Libmacgpg.h>


typedef enum {
	NewKeyAction,
	AddSubkeyAction,
	AddUserIDAction,
	AddSignatureAction,
	ChangeExpirationDateAction,
	SearchKeysAction,
	ReceiveKeysAction,
	ShowFoundKeysAction,
	AlgorithmPreferencesAction
} SheetAction;

@interface KeyLengthFormatter : NSFormatter {
	NSInteger minKeyLength;
	NSInteger maxKeyLength;
}
@property NSInteger minKeyLength;
@property NSInteger maxKeyLength;
- (NSInteger)checkedValue:(NSInteger)value;
@end




@interface SheetController : NSObject {

	SheetAction currentAction;
	
	//Objekte für die XXX_Action Methoden.
	GPGKey *myKeyInfo;
	GPGSubkey *mySubkey;
	NSString *myString;
	
	NSArray *userIDs;
	
	
	BOOL allowEdit;
	
	//Für Öffnen- und Speichern-Sheets.
	IBOutlet NSView *exportKeyOptionsView;
	
	NSSavePanel *savePanel;
	NSOpenPanel *openPanel;
	
	BOOL allowSecretKeyExport;
	NSInteger exportFormat;
	
	NSInteger lastReturnCode;
	
	
	IBOutlet KeyLengthFormatter *keyLengthFormatter;
	IBOutlet NSWindow *sheetWindow;
	IBOutlet NSView *sheetView;
	
	//Views die im Fenster angezeigt werden können.
	IBOutlet NSView *progressView;
	IBOutlet NSView *newKeyView;
	IBOutlet NSView *newKey_passphraseSubview;
	IBOutlet NSView *newKey_topSubview;
	IBOutlet NSView *generateSubkeyView;
	IBOutlet NSView *generateUserIDView;
	IBOutlet NSView *generateSignatureView;
	IBOutlet NSView *changeExpirationDateView;
	IBOutlet NSView *searchKeysView;
	IBOutlet NSView *foundKeysView;
	IBOutlet NSView *receiveKeysView;
	IBOutlet NSView *resultView;
	IBOutlet NSView *editAlgorithmPreferencesView;
	
	
	IBOutlet NSProgressIndicator *progressIndicator;
	NSView *displayedView;
	
	NSArray *foundKeys;
	IBOutlet NSArrayController *foundKeysController;
	
	NSString *msgText;
	NSArray *emailAddresses;
	NSArray *secretKeys;
	NSArray *secretKeyFingerprints;
	NSInteger secretKeyId;
	
	NSString *pattern;
	NSString *name;
	NSString *email;
	NSString *comment;
	NSString *passphrase;
	NSString *confirmPassphrase;	
	NSInteger keyType;
	NSInteger sigType;
	BOOL hasExpirationDate;
	NSDate *expirationDate;
	NSDate *minExpirationDate;
	NSDate *maxExpirationDate;
	NSArray *availableLengths;
	NSInteger length;
	BOOL localSig;
	
}

@property BOOL allowSecretKeyExport;
@property NSInteger exportFormat;


@property (retain) GPGKey *myKeyInfo;
@property (retain) NSString *myString;
@property (retain) GPGSubkey *mySubkey;
@property (retain) NSArray *userIDs;
@property BOOL allowEdit;


@property (retain) NSArray *foundKeys;


@property (retain) NSString *msgText;
@property (retain) NSArray *emailAddresses;
@property (copy) NSArray *secretKeys;
@property (copy) NSArray *secretKeyFingerprints;
@property NSInteger secretKeyId;

@property (retain) NSString *pattern;
@property (retain) NSString *name;
@property (retain) NSString *email;
@property (retain) NSString *comment;
@property (retain) NSString *passphrase;
@property (retain) NSString *confirmPassphrase;
@property (retain) NSArray *availableLengths;
@property NSInteger keyType;
@property NSInteger sigType;
@property NSInteger length;
@property BOOL hasExpirationDate;
@property (retain) NSDate *expirationDate;
@property (retain) NSDate *minExpirationDate;
@property (retain) NSDate *maxExpirationDate;
@property BOOL localSig;


@property (assign) NSView *displayedView;


+ (id)sharedInstance;
- (void)addSubkey:(GPGKey *)keyInfo;
- (void)addUserID:(GPGKey *)keyInfo;
- (void)addSignature:(GPGKey *)keyInfo userID:(NSString *)userID;
- (void)changeExpirationDate:(GPGKey *)keyInfo subkey:(GPGSubkey *)subkey;
- (void)searchKeys;
- (void)searchKeys_Action;
- (void)showFoundKeys:(NSArray *)keys;
- (void)receiveKeys;
- (void)receiveKeys_Action:(NSSet *)keyIDs;
- (void)generateNewKey;
- (void)algorithmPreferences:(GPGKey *)keyInfo editable:(BOOL)editable;
- (void)algorithmPreferences_Action;

- (void)addPhoto:(GPGKey *)keyInfo;
- (void)importKey;
- (void)exportKeys:(NSSet *)keyInfos;

- (void)genRevokeCertificateForKey:(GPGKey *)keyInfo;


- (void)showResult:(NSString *)text;
- (void)showResultText:(NSString *)text;



- (void)runSheetForWindow:(NSWindow *)window;
- (void)closeSheet;
- (void)setStandardExpirationDates;
- (void)setDataFromAddressBook;


- (IBAction)okButton:(id)sender;
- (IBAction)cancelButton:(id)sender;
- (IBAction)backButton:(id)sender;

- (BOOL)checkName;
- (BOOL)checkEmailMustSet:(BOOL)mustSet;
- (BOOL)checkComment;
- (BOOL)checkPassphrase;

- (NSInteger)alertSheetForWindow:(NSWindow *)window messageText:(NSString *)messageText infoText:(NSString *)infoText defaultButton:(NSString *)button1 alternateButton:(NSString *)button2 otherButton:(NSString *)button3;
- (void)alertDidEnd:(NSAlert *)alert returnCode:(NSInteger)returnCode contextInfo:(void *)contextInfo;

- (void)openSavePanelDidEnd:(NSOpenPanel *)sheet returnCode:(int)returnCode contextInfo:(NSDictionary *)contextInfo;
- (BOOL)panel:(NSOpenPanel *)sender validateURL:(NSURL *)url error:(NSError **)outError;

@end



