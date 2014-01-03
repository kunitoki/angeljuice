/*
  ==============================================================================

   This file is part of AngelJuice

   which is based on kRAkEn/gORe eJUCE library
   which uses
               Raw Material Software ltd. JUCE library
               AngelCode AngelScript scripting library

   AngelJuice can be redistributed and/or modified under the terms of the
   GNU General Public License, as published by the Free Software Foundation;
   either version 2 of the License, or (at your option) any later version.

   AngelJuice is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with eJUCE; if not, visit www.gnu.org/licenses or write to the
   Free Software Foundation, Inc., 59 Temple Place, Suite 330,
   Boston, MA 02111-1307 USA

   @coder	Asnaghi Lucio a.k.a. kRAkEn/gORe

  ==============================================================================
*/

#include "AngelJuice_ProjectTree.h"


//==============================================================================
class TreeViewDemoItem  : public TreeViewItem
{
    XmlElement* xml;

public:
    TreeViewDemoItem (XmlElement* const xml_)
        : xml (xml_)
    {
    }

    ~TreeViewDemoItem()
    {
    }

    int getItemWidth() const
    {
        return xml->getIntAttribute (T("width"), -1);
    }

    const String getUniqueName() const
    {
        if (xml != 0)
            return xml->getStringAttribute (T("name"), String::empty);
        else
            return String::empty;
    }

    bool mightContainSubItems()
    {
        return xml != 0
                && xml->getFirstChildElement() != 0;
    }

    void paintItem (Graphics& g, int width, int height)
    {
        if (xml != 0)
        {
            // if this item is selected, fill it with a background colour..
            if (isSelected())
                g.fillAll (Colours::blue.withAlpha (0.3f));

            // use a "colour" attribute in the xml tag for this node to set the text colour..
            g.setColour (Colour (xml->getStringAttribute (T("colour"), T("ff000000")).getHexValue32()));

            g.setFont (*(GlobalConfig::getInstance()->editorFont));

            // draw the xml element's tag name..
            g.drawText (xml->getStringAttribute (T("name"), T(" ")),
                        4, 0, width - 4, height,
                        Justification::centredLeft, true);
        }
    }

    void itemOpennessChanged (bool isNowOpen)
    {
        if (isNowOpen)
        {
            // if we've not already done so, we'll now add the tree's sub-items. You could
            // also choose to delete the existing ones and refresh them if that's more suitable
            // in your app.
            if (getNumSubItems() == 0)
            {
                // create and add sub-items to this node of the tree, corresponding to
                // each sub-element in the XML..

                if (xml != 0)
                {
                    forEachXmlChildElement (*xml, child)
                    {
                        addSubItem (new TreeViewDemoItem (child));
                    }
                }
            }
        }
        else
        {
            // in this case, we'll leave any sub-items in the tree when the node gets closed,
            // though you could choose to delete them if that's more appropriate for
            // your application.
        }
    }
};

//==============================================================================
ProjectTreeView::ProjectTreeView (AngelJuiceComponent* holder_)
    : holder (holder_)
{
    const String treeXmlString (
        "<workspace name='Default workspace'>"
        "   <project name='Empty project'>"
        "       <file name='Untitled' colour='ffff0000' />"
        "       <file name='test.ajs' colour='ffff0000' width='50' />"
        "       <file name='other_test.ajs' colour='ff8866ee' />"
        "       <dir name='includes' >"
        "           <subnode><subnode width='50' /></subnode>"
        "       </dir>"
        "   </project>"
        "</workspace>");

    XmlDocument parser (treeXmlString);

    treeXml = parser.getDocumentElement();

    rootItem = new TreeViewDemoItem (treeXml);
    rootItem->setOpen (true);

    addAndMakeVisible (treeView = new TreeView());

    treeView->setIndentSize (16);
    treeView->setRootItem (rootItem);
}

ProjectTreeView::~ProjectTreeView()
{
    deleteAllChildren();

    if (rootItem != 0)
        delete rootItem;

    if (treeXml != 0)
        delete treeXml;
}

void ProjectTreeView::paint (Graphics& g)
{
    g.setColour (Colours::white);
    g.fillRect (treeView->getX(), treeView->getY(),
                treeView->getWidth(), treeView->getHeight());

    g.setColour (Colours::grey);
    g.drawRect (treeView->getX(), treeView->getY(),
                treeView->getWidth(), treeView->getHeight());
}

void ProjectTreeView::resized()
{
    treeView->setBounds (0, 0, getWidth(), getHeight());
}
