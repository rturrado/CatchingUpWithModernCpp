#ifndef FACES_H
#define FACES_H

#include "RtcPrettyPrint.h"

#include <iomanip>  // fixed, setprecision
#include <ostream>
#include <vector>


namespace rtc::face_detection
{
    struct Error
    {
        std::string code{};
        std::string message{};

        void print(std::ostream& os) const {
            os << "(code: " << code << ", message: '" << message << "')";
        }
    };
    inline std::ostream& operator<<(std::ostream& os, const Error& error) { error.print(os); return os; }


    struct ErrorResponse
    {
        Error error{};

        void print(std::ostream& os, const FillLineStart& fill_line_start = {}) const {
            os << fill_line_start << "Error: "; error.print(os);
        }
    };
    inline std::ostream& operator<<(std::ostream& os, const ErrorResponse& error_response) { error_response.print(os); return os; }


    struct Point
    {
        int x{};
        int y{};

        auto operator<=>(const Point& other) const = default;

        void print(std::ostream& os) const {
            os << "(x: " << x << ", y: " << y << ")";
        }
    };
    inline std::ostream& operator<<(std::ostream& os, const Point& point) { point.print(os); return os; }

    
    struct Rectangle
    {
        int top{};
        int left{};
        int width{};
        int height{};

        auto operator<=>(const Rectangle& other) const = default;

        void print(std::ostream& os) const {
            os << "(top: " << top << ", left: " << left << ", width: " << width << ", height: " << height << ")";
        }
    };
    inline std::ostream& operator<<(std::ostream& os, const Rectangle& rectangle) { rectangle.print(os); return os; }


    struct FaceLandmarks
    {
        Point pupilLeft{};
        Point pupilRight{};
        Point noseTip{};
        Point mouthLeft{};
        Point mouthRight{};
        Point eyebrowLeftOuter{};
        Point eyebrowLeftInner{};
        Point eyeLeftOuter{};
        Point eyeLeftTop{};
        Point eyeLeftBottom{};
        Point eyeLeftInner{};
        Point eyebrowRightInner{};
        Point eyebrowRightOuter{};
        Point eyeRightInner{};
        Point eyeRightTop{};
        Point eyeRightBottom{};
        Point eyeRightOuter{};
        Point noseRootLeft{};
        Point noseRootRight{};
        Point noseLeftAlarTop{};
        Point noseRightAlarTop{};
        Point noseLeftAlarOutTip{};
        Point noseRightAlarOutTip{};
        Point upperLipTop{};
        Point upperLipBottom{};
        Point underLipTop{};
        Point underLipBottom{};

        auto operator<=>(const FaceLandmarks& other) const = default;

        void print(std::ostream& os, const FillLineStart& fill_line_start = {}) const {
            os << fill_line_start << "Face landmarks:\n";
            os << (fill_line_start + 1) << "pupilLeft: "; pupilLeft.print(os); os << "\n";
            os << (fill_line_start + 1) << "pupilRight: "; pupilRight.print(os); os << "\n";
            os << (fill_line_start + 1) << "noseTip: "; noseTip.print(os); os << "\n";
            os << (fill_line_start + 1) << "mouthLeft: "; mouthLeft.print(os); os << "\n";
            os << (fill_line_start + 1) << "mouthRight: "; mouthRight.print(os); os << "\n";
            os << (fill_line_start + 1) << "eyebrowLeftOuter: "; eyebrowLeftOuter.print(os); os << "\n";
            os << (fill_line_start + 1) << "eyebrowLeftInner: "; eyebrowLeftInner.print(os); os << "\n";
            os << (fill_line_start + 1) << "eyeLeftOuter: "; eyeLeftOuter.print(os); os << "\n";
            os << (fill_line_start + 1) << "eyeLeftTop: "; eyeLeftTop.print(os); os << "\n";
            os << (fill_line_start + 1) << "eyeLeftBottom: "; eyeLeftBottom.print(os); os << "\n";
            os << (fill_line_start + 1) << "eyeLeftInner: "; eyeLeftInner.print(os); os << "\n";
            os << (fill_line_start + 1) << "eyebrowRightInner: "; eyebrowRightInner.print(os); os << "\n";
            os << (fill_line_start + 1) << "eyebrowRightOuter: "; eyebrowRightOuter.print(os); os << "\n";
            os << (fill_line_start + 1) << "eyeRightInner: "; eyeRightInner.print(os); os << "\n";
            os << (fill_line_start + 1) << "eyeRightTop: "; eyeRightTop.print(os); os << "\n";
            os << (fill_line_start + 1) << "eyeRightBottom: "; eyeRightBottom.print(os); os << "\n";
            os << (fill_line_start + 1) << "eyeRightOuter: "; eyeRightOuter.print(os); os << "\n";
            os << (fill_line_start + 1) << "noseRootLeft: "; noseRootLeft.print(os); os << "\n";
            os << (fill_line_start + 1) << "noseRootRight: "; noseRootRight.print(os); os << "\n";
            os << (fill_line_start + 1) << "noseLeftAlarTop: "; noseLeftAlarTop.print(os); os << "\n";
            os << (fill_line_start + 1) << "noseRightAlarTop: "; noseRightAlarTop.print(os); os << "\n";
            os << (fill_line_start + 1) << "noseLeftAlarOutTip: "; noseLeftAlarOutTip.print(os); os << "\n";
            os << (fill_line_start + 1) << "noseRightAlarOutTip: "; noseRightAlarOutTip.print(os); os << "\n";
            os << (fill_line_start + 1) << "upperLipTop: "; upperLipTop.print(os); os << "\n";
            os << (fill_line_start + 1) << "upperLipBottom: "; upperLipBottom.print(os); os << "\n";
            os << (fill_line_start + 1) << "underLipTop: "; underLipTop.print(os); os << "\n";
            os << (fill_line_start + 1) << "underLipBottom: "; underLipBottom.print(os); os << "\n";
        }
    };
    inline std::ostream& operator<<(std::ostream& os, const FaceLandmarks& face_landmarks) { face_landmarks.print(os); return os; }


    struct Emotion
    {
        double anger{};
        double contempt{};
        double disgust{};
        double fear{};
        double happiness{};
        double neutral{};
        double sadness{};
        double surprise{};

        auto operator<=>(const Emotion& other) const = default;

        void print(std::ostream& os, const FillLineStart& fill_line_start = {}) const {
            os << fill_line_start << "Emotion:\n";
            os << (fill_line_start + 1) << "anger: " << std::fixed << std::setprecision(3) << anger << "\n";
            os << (fill_line_start + 1) << "contempt: " << std::fixed << std::setprecision(3) << contempt << "\n";
            os << (fill_line_start + 1) << "disgust: " << std::fixed << std::setprecision(3) << disgust << "\n";
            os << (fill_line_start + 1) << "fear: " << std::fixed << std::setprecision(3) << fear << "\n";
            os << (fill_line_start + 1) << "happiness: " << std::fixed << std::setprecision(3) << happiness << "\n";
            os << (fill_line_start + 1) << "neutral: " << std::fixed << std::setprecision(3) << neutral << "\n";
            os << (fill_line_start + 1) << "sadness: " << std::fixed << std::setprecision(3) << sadness << "\n";
            os << (fill_line_start + 1) << "surprise: " << std::fixed << std::setprecision(3) << surprise << "\n";
        }
    };
    inline std::ostream& operator<<(std::ostream& os, const Emotion& emotion) { emotion.print(os); return os; }


    struct FaceAttributes
    {
        std::string gender{};
        double age{};
        Emotion emotion{};

        auto operator<=>(const FaceAttributes& other) const = default;

        void print(std::ostream& os, const FillLineStart& fill_line_start = {}) const {
            os << fill_line_start << "Face attributes:\n";
            os << (fill_line_start + 1) << "gender: " << gender << "\n";
            os << (fill_line_start + 1) << "age: " << std::fixed << std::setprecision(1) << age << "\n";
            emotion.print(os, fill_line_start + 1);
        }
    };
    inline std::ostream& operator<<(std::ostream& os, const FaceAttributes& face_attributes) { face_attributes.print(os); return os; }


    struct Face
    {
        std::string id{};
        Rectangle rectangle{};
        FaceLandmarks landmarks{};
        FaceAttributes attributes{};

        auto operator<=>(const Face& other) const = default;

        void print(std::ostream& os, const FillLineStart& fill_line_start = {}) const {
            os << fill_line_start << "Face:\n";
            os << (fill_line_start + 1) << "id: " << id << "\n";
            os << (fill_line_start + 1) << "rectangle: "; rectangle.print(os); os << "\n";
            landmarks.print(os, fill_line_start + 1);
            attributes.print(os, fill_line_start + 1);
        }
    };
    inline std::ostream& operator<<(std::ostream& os, const Face& face) { face.print(os); return os; }


    struct FacesResponse
    {
        std::vector<Face> faces{};

        auto operator<=>(const FacesResponse& other) const = default;

        void print(std::ostream& os, const FillLineStart& fill_line_start = {}) const {
            os << fill_line_start << "Faces:\n";
            for (auto&& face : faces) {
                face.print(os, fill_line_start + 1);
            }
        }
    };
    inline std::ostream& operator<<(std::ostream& os, const FacesResponse& faces_response) { faces_response.print(os); return os; }

}  // namespace rtc::face_detection


#endif  // FACE_H
