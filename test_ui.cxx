
#include "test_ui.hxx"
#include "avtk/utils.hxx"
#include "avtk/theme.hxx"

#include "libs/audioGen.hxx"

#include <sstream>

TestUI::TestUI( PuglNativeWindow parent ):
  Avtk::UI( 810, 530, parent )
{
  themes.push_back( new Avtk::Theme( this, "orange.avtk" ) );
  themes.push_back( new Avtk::Theme( this, "green.avtk" ) );
  themes.push_back( new Avtk::Theme( this, "yellow.avtk" ) );
  
  Widget::theme_ = themes.front();
  
  Avtk::Widget* w = 0;
  
  // image
  Avtk::Image* i = new Avtk::Image( this, 0, 0, 810, 36, "Image" );
  i->load( header.pixel_data );
  
  // group testing
  w = new Avtk::Box( this, 610, 43, 100, 125, "Items" );
  group1 = new Avtk::Group( this, 610, 43+16, 100, 0, "Group 1" );
  group1->mode( Avtk::Group::WIDTH_EQUAL );
  group1->valueMode ( Group::VALUE_SINGLE_CHILD );
  group1->resizeMode( Group::RESIZE_FIT_TO_CHILDREN );
  
  w = new Avtk::ListItem( this, 7, 45, 90, 11, "Item 1" );
  group1->add( w );
  w = new Avtk::ListItem( this, 7, 45, 90, 11, "Item 2" );
  group1->add( w );
  w = new Avtk::ListItem( this, 7, 45, 90, 11, "Item 3" );
  group1->add( w );
  w = new Avtk::ListItem( this, 7, 45, 90, 11, "Item 4" );
  group1->add( w );
  w->value( 1 );
  w = new Avtk::ListItem( this, 7, 45, 90, 11, "Item 5" );
  group1->add( w );
  w = new Avtk::ListItem( this, 7, 45, 90, 11, "Item 6" );
  group1->add( w );
  w = new Avtk::ListItem( this, 7, 45, 90, 11, "Item 7" );
  group1->add( w );
  w = new Avtk::ListItem( this, 7, 45, 90, 11, "Item 8" );
  group1->add( w );
  w = new Avtk::ListItem( this, 7, 45, 90, 11, "Item 9" );
  group1->add( w );
  
  group1->end();
  
  
  
  
  // Editor
  w = new Avtk::Box( this, 130, 43, 120*3, 60*3+14, "MIDI Editor" );
  scroll = new Avtk::Scroll( this, 130, 43+15, 120*3, 60*3, "Scroll 1" );
  scroll->setCtrlZoom( true );
  int scale = 4;
  editor = new Avtk::EventEditor( this, 0, 0, 240*scale, 250*scale, "EventEditor" );
  editor->value( true );
  editor->visible( true );
  scroll->set( editor );
  scroll->end();
  
  /*
  // slider vert
  vertSlider = new Avtk::Slider( this, 755,  40, 22, 320, "Vertical   Slider" );
  horiSlider = new Avtk::Slider( this, 130, 365, 620, 22, "Horizontal Slider" );
  
  vertSlider->value ( 1.0 );
  horiSlider->value ( 0.5 );
  scroll->vertical  ( 1.0 );
  scroll->horizontal( 0.5 );
  */
  
  
  // button
  momentary = new Avtk::Button( this, 7, 45, 90, 22, "Zoom In" );
  momentary->theme( theme( 1 ) );
  momentary->clickMode( Avtk::Widget::CLICK_MOMENTARY );
  
  
  momentaryOut = new Avtk::Button( this, 7, 69, 90, 22, "Zoom Out" );
  momentaryOut->theme( theme( 2 ) );
  //momentaryOut->clickMode( Avtk::Widget::CLICK_TOGGLE );
  momentaryOut->clickMode( Avtk::Widget::CLICK_MOMENTARY );
  
  
  // button
  groupToggler = new Avtk::Button( this, 25, 245, 130, 22, "Group Toggler" );
  groupToggler->theme( theme( 2 ) );
  groupToggler->clickMode( Avtk::Widget::CLICK_TOGGLE );
  
  // dial
  w = new Avtk::Dial( this, 7, 85, 75, 75, "Dial 1" );
  
  // number
  w = new Avtk::Number( this, 85, 85, 35, 25, "Number box" );
  
  
  w = new Avtk::Box( this, 500, 43, 105, 125, "Files" );
  std::string stripped;
  std::vector<std::string> items;
  Avtk::directoryContents(  "files/", items, stripped, true, true );
  list2 = new Avtk::List( this, 500, 43+16, 105, 125, "FileList" );
  list2->show( items );
  list2->end();
  
  
  // waveform
  w = new Avtk::Box( this, 130, 250, 250, 14, "Waveform" );
  waveform = new Avtk::Waveform( this, 130, 250+16, 250, 100, "Waveform" );
  std::vector<float> tmp;
  int error = Avtk::loadSample( "test.wav", tmp );
  waveform->show( tmp );
  
  // spectrum
  w = new Avtk::Box( this, 385, 250, 250, 14, "Spectrum" );
  spectrum = new Avtk::Spectrum( this, 385, 250+16, 250, 100, "Spectrum" );
  
  std::vector<float> audio;
  for(int i = 0; i < 44100; i++)
    audio.push_back( 0 );
  // gen audio
  sawtooth( 1024, &audio[0], 440, 100 );
  // analyse it
  audioDataSpectrum( 1024, &audio[0] );
  // set it to widget
  spectrum->show( 1024, &audio[0] );
  
  
  // ADSR
  w = new Avtk::Box( this, 640, 250, 120, 14, "Envelope" );
  w = new Avtk::Envelope( this, 640, 250+16, 120, 100, "Envelope" );
  
  /*
  // slider horizontal
  w =  new Avtk::Slider( this,  15,350, 250, 22, "Zoom" );
  w =  new Avtk::Slider( this,  15,374, 250, 22, "Vol" );
  */
  
  
  
  
  /*
  scroll = new Avtk::Scroll( this, 130, 43, 520, 210, "Scroll 1" );
  // list
  list = new Avtk::List( this, 345, 345, 105, 425, "List (Left)" );
  Avtk::directoryContents(  "/root/openav/content/", items, stripped);
  std::vector<std::string> items2;
  items2.push_back( items.at(0) );
  list->show( items );
  list->mode      ( Group::WIDTH_EQUAL );
  list->valueMode ( Group::VALUE_SINGLE_CHILD );
  //list->resizeMode( Group::RESIZE_FIT_TO_CHILDREN );
  scroll->set( list );
  //scroll->set( group1 );
  list->end();
  */
  
  
}

void TestUI::widgetValueCB( Avtk::Widget* w )
{
  if( w == momentary )
  {
    //editor->zoom( 1 );
    //((Avtk::Scroll*)editor->parent())->childResize( editor );
    //w = new Avtk::ListItem( this, 7, 45, 90, 11, "Group dyn" );
    //group1->add( w );
  }
  else if( w == momentaryOut )
  {
    //editor->zoom( 0 );
    //((Avtk::Scroll*)editor->parent())->childResize( editor );
  }
  else if( w == vertSlider )
  {
    //scroll->vertical( w->value() );
  }
  else if( w == horiSlider )
  {
    //scroll->horizontal( w->value() );
  }
  else
  {
    printf( "%s, value = %f\n", w->label(), w->value() );
  }
}

