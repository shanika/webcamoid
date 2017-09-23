/* Webcamoid, webcam capture application.
 * Copyright (C) 2011-2017  Gonzalo Exequiel Pedone
 *
 * Webcamoid is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Webcamoid is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Webcamoid. If not, see <http://www.gnu.org/licenses/>.
 *
 * Web-Site: http://webcamoid.github.io/
 */

#ifndef VIDEODISPLAY_H
#define VIDEODISPLAY_H

#include <QMutex>
#include <QQuickItem>
#include <QSGSimpleTextureNode>

#include "akutils.h"

typedef QSharedPointer<QSGTexture> TexturePtr;

class VideoDisplay: public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(VideoDisplay)

    Q_PROPERTY(bool fillDisplay
               READ fillDisplay
               WRITE setFillDisplay
               RESET resetFillDisplay
               NOTIFY fillDisplayChanged)

    public:
        VideoDisplay(QQuickItem *parent=nullptr);
        ~VideoDisplay();

        Q_INVOKABLE bool fillDisplay() const;

    private:
        bool m_fillDisplay;
        TexturePtr m_videoFrame;
        QImage m_frame;
        QMutex m_mutex;

    protected:
        QSGNode *updatePaintNode(QSGNode *oldNode,
                                 UpdatePaintNodeData *updatePaintNodeData);

    signals:
        void fillDisplayChanged();

    public slots:
        void iStream(const AkPacket &packet);
        void setFillDisplay(bool fillDisplay);
        void resetFillDisplay();
};

#endif // VIDEODISPLAY_H
