/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQml 2.0
import QtQuick 2.5
import Qt.UniUIKitControls 1.0

ViewController {
    id: tab3

    tabBarItem: TabBarItem {
        title: "Tab 3"
    }

    view: View {

        TableView {
            y: 30
            width: parent.width
            height: parent.height;
            dataSource: planetsDataSource
        }

        TableViewDataSource {
            id: planetsDataSource
            property var planets: ["Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptun"]
            property var distances: ["0.39", "0.72", "1", "1.52", "1.52", "5.20", "9.53", "19.18", "30.06"]

            numberOfSectionsInTableView: 10
            numberOfRowsInSection: planets.length

            titleForHeaderInSection: function(tableView, section) {
                return "Section " + section;
            }

            sectionIndexTitlesForTableView: function(tableView) {
                var titles = [];
                var sectionCount = numberOfSectionsInTableView(tableView);
                for (var i = 0; i < sectionCount; ++i)
                    titles[i]  = "Section " + i;
                return titles;
            }

            cellForRowAtIndexPath: function(tableView, indexPath) {
                var reuseId = "planetcell" + (indexPath.section % 2);
                var cell = tableView.dequeueReusableCellWithIdentifier(reuseId);
                if (cell === null)
                    cell = planetsCellComponent.createObject(tableView, { reuseIdentifier: reuseId, section: indexPath.section });

                cell.textLabel.text = planets[indexPath.row];
                cell.detailTextLabel.text = distances[indexPath.row] + " AU"
                return cell;
            }

            Component {
                id: planetsCellComponent
                TableViewCell {
                    property var section
                    cellStyle: TableViewCell.StyleValue1
                    backgroundColor: section % 2 ? Qt.rgba(0.90, 0.90, 0.95, 255) : Qt.rgba(1., 1., 1. ,255)
                }
            }
        }
    }
}